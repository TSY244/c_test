
#include"threadpool.h"


const int NUMBER = 2;


// 任务结构体
typedef struct Task
{
    void (*function)(void* arg);
    void* arg;
}Task;


// 线程池结构体
struct ThreadPool
{
    // 任务队列
    Task* taskQ;
    int queueCapacity;  // 容量
    int queueSize;      // 当前任务个数
    int queueFront;     // 队头 -> 取数据
    int queueRear;      // 队尾 -> 放数据

    pthread_t managerID;    // 管理者线程ID
    pthread_t* threadIDs;   // 工作的线程ID
    int minNum;             // 最小线程数量
    int maxNum;             // 最大线程数量
    int busyNum;            // 忙的线程的个数
    int liveNum;            // 存活的线程的个数
    int exitNum;            // 要销毁的线程个数
    pthread_mutex_t mutexPool;  // 锁整个的线程池
    pthread_mutex_t mutexBusy;  // 锁busyNum变量
    pthread_cond_t notFull;     // 任务队列是不是满了
    pthread_cond_t notEmpty;    // 任务队列是不是空了

    int shutdown;           // 是不是要销毁线程池, 销毁为1, 不销毁为0
};

ThreadPool* threadPoolCreate(int min, int max, int queueSize)
{
    ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
    do
    {
        if (pool == NULL)
        {
            printf("malloc threadpool fail...\n");
            break;
        }

        pool->threadIDs = (pthread_t*)malloc(sizeof(pthread_t) * max);
        if (pool->threadIDs == NULL)
        {
            printf("malloc threadIDs fail...\n");
            break;
        }
        memset(pool->threadIDs, 0, sizeof(pthread_t) * max);
        pool->minNum = min;
        pool->maxNum = max;
        pool->busyNum = 0;
        pool->liveNum = min;    // 和最小个数相等
        pool->exitNum = 0;

        if (pthread_mutex_init(&pool->mutexPool, NULL) != 0 ||
            pthread_mutex_init(&pool->mutexBusy, NULL) != 0 ||
            pthread_cond_init(&pool->notEmpty, NULL) != 0 ||
            pthread_cond_init(&pool->notFull, NULL) != 0)
        {
            printf("mutex or condition init fail...\n");
            break;
        }

        // 任务队列
        pool->taskQ = (Task*)malloc(sizeof(Task) * queueSize);
        pool->queueCapacity = queueSize;
        pool->queueSize = 0;
        pool->queueFront = 0;
        pool->queueRear = 0;

        pool->shutdown = 0;

        // 创建线程
        pthread_create(&pool->managerID, NULL, manager, pool);
        for (int i = 0; i < min; ++i)
        {
            pthread_create(&pool->threadIDs[i], NULL, worker, pool);
        }
        return pool;
    } while (0);

    // 释放资源
    if (pool && pool->threadIDs) free(pool->threadIDs);
    if (pool && pool->taskQ) free(pool->taskQ);
    if (pool) free(pool);

    return NULL;
}

int threadPoolDestroy(ThreadPool* pool)
{
    if (pool == NULL)
    {
        return -1;
    }

    // 关闭线程池
    pool->shutdown = 1;
    // 阻塞回收管理者线程
    pthread_join(pool->managerID, NULL);
    // 唤醒阻塞的消费者线程
    for (int i = 0; i < pool->liveNum; ++i)
    {
        pthread_cond_signal(&pool->notEmpty);
    }
    // 释放堆内存
    if (pool->taskQ)
    {
        free(pool->taskQ);
    }
    if (pool->threadIDs)
    {
        free(pool->threadIDs);
    }

    pthread_mutex_destroy(&pool->mutexPool);
    pthread_mutex_destroy(&pool->mutexBusy);
    pthread_cond_destroy(&pool->notEmpty);
    pthread_cond_destroy(&pool->notFull);

    free(pool);
    pool = NULL;

    return 0;
}

void threadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg)
{
    pthread_mutex_lock(&pool->mutexPool);
    while (pool->queueSize == pool->queueCapacity && !pool->shutdown)
    {
        // 阻塞生产者线程
        pthread_cond_wait(&pool->notFull, &pool->mutexPool);
    }
    if (pool->shutdown)
    {
        pthread_mutex_unlock(&pool->mutexPool);
        return;
    }
    // 添加任务
    pool->taskQ[pool->queueRear].function = func;
    pool->taskQ[pool->queueRear].arg = arg;
    pool->queueRear = (pool->queueRear + 1) % pool->queueCapacity;
    pool->queueSize++;

    pthread_cond_signal(&pool->notEmpty);
    pthread_mutex_unlock(&pool->mutexPool);
}

int threadPoolBusyNum(ThreadPool* pool)
{
    pthread_mutex_lock(&pool->mutexBusy);
    int busyNum = pool->busyNum;
    pthread_mutex_unlock(&pool->mutexBusy);
    return busyNum;
}

int threadPoolAliveNum(ThreadPool* pool)
{
    pthread_mutex_lock(&pool->mutexPool);
    int aliveNum = pool->liveNum;
    pthread_mutex_unlock(&pool->mutexPool);
    return aliveNum;
}

void* worker(void* arg)
{
    ThreadPool* pool = (ThreadPool*)arg;

    while (1)
    {
        pthread_mutex_lock(&pool->mutexPool);
        // 当前任务队列是否为空
        while (pool->queueSize == 0 && !pool->shutdown)
        {
            // 阻塞工作线程
            pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);

            // 判断是不是要销毁线程
            if (pool->exitNum > 0)
            {
                pool->exitNum--;
                if (pool->liveNum > pool->minNum)
                {
                    pool->liveNum--;
                    pthread_mutex_unlock(&pool->mutexPool);
                    threadExit(pool);
                }
            }
        }

        // 判断线程池是否被关闭了
        if (pool->shutdown)
        {
            pthread_mutex_unlock(&pool->mutexPool);
            threadExit(pool);
        }

        // 从任务队列中取出一个任务
        Task task;
        task.function = pool->taskQ[pool->queueFront].function;
        task.arg = pool->taskQ[pool->queueFront].arg;
        // 移动头结点
        pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;
        pool->queueSize--;
        // 解锁
        pthread_cond_signal(&pool->notFull);
        pthread_mutex_unlock(&pool->mutexPool);

        printf("thread %ld start working...\n", pthread_self());
        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum++;
        pthread_mutex_unlock(&pool->mutexBusy);
        task.function(task.arg);
        free(task.arg);
        task.arg = NULL;

        printf("thread %ld end working...\n", pthread_self());
        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexBusy);
    }
    return NULL;
}

void* manager(void* arg)
{
    ThreadPool* pool = (ThreadPool*)arg;
    while (!pool->shutdown)
    {
        // 每隔3s检测一次
        sleep(3);

        // 取出线程池中任务的数量和当前线程的数量
        pthread_mutex_lock(&pool->mutexPool);
        int queueSize = pool->queueSize;
        int liveNum = pool->liveNum;
        pthread_mutex_unlock(&pool->mutexPool);

        // 取出忙的线程的数量
        pthread_mutex_lock(&pool->mutexBusy);
        int busyNum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);

        // 添加线程
        // 任务的个数>存活的线程个数 && 存活的线程数<最大线程数
        if (queueSize > liveNum && liveNum < pool->maxNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            int counter = 0;
            for (int i = 0; i < pool->maxNum && counter < NUMBER
                && pool->liveNum < pool->maxNum; ++i)
            {
                if (pool->threadIDs[i] == 0)
                {
                    pthread_create(&pool->threadIDs[i], NULL, worker, pool);
                    counter++;
                    pool->liveNum++;
                }
            }
            pthread_mutex_unlock(&pool->mutexPool);
        }
        // 销毁线程
        // 忙的线程*2 < 存活的线程数 && 存活的线程>最小线程数
        if (busyNum * 2 < liveNum && liveNum > pool->minNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            pool->exitNum = NUMBER;
            pthread_mutex_unlock(&pool->mutexPool);
            // 让工作的线程自杀
            for (int i = 0; i < NUMBER; ++i)
            {
                pthread_cond_signal(&pool->notEmpty);
            }
        }
    }
    return NULL;
}

void threadExit(ThreadPool* pool)
{
    pthread_t tid = pthread_self();
    for (int i = 0; i < pool->maxNum; ++i)
    {
        if (pool->threadIDs[i] == tid)
        {
            pool->threadIDs[i] = 0;
            printf("threadExit() called, %ld exiting...\n", tid);
            break;
        }
    }
    pthread_exit(NULL);
}






//
//
////任务结构体
//typedef struct Task
//{
//	void (*function)(void* arg);
//	void* arg;
//}Task;
//
//
//
////线程池结构体
//struct ThreadPool
//{
//	Task* taskQ;
//	int queueCapacity;  //容量
//	int queueSize;      //当前任务的个数
//	int queueFront;     //队头 ->取数据
//	int queueRear;      //队尾 ->放数据
//
//	pthread_t manegeID;    //管理者ID   pthread_t  无符号长整型
//	pthread_t* threadIDs;  //工作的线程ID
//	int minNum;            //最小线程数
//	int maxNum;            //最大线程数
//	int busyNum;           //忙的线程数
//	int liveNum;           //活着的线程数
//	int exitNum;           //杀死的线程数
//	pthread_mutex_t mutexPool;   //锁整个线程池   pthread_mutex_t  联合体类型
//	pthread_mutex_t mutexBusy;   //锁工作的线程
//	pthread_cond_t notEmpty;   //判断是不是空了   pthread_cond_t  联合体 
//	pthread_cond_t notFull;    //判断是不是满了
//
//
//	int shutdown;          //是不是销毁线程池，销毁为1，不销毁为0
//};



//ThreadPool* threadPoolCreate(int min, int max, int queueSize)
//{
//	ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
//	do
//	{
//		if (NULL == pool)
//		{
//			My_error("malloc pool");
//			break;
//		}
//		pool->threadIDs = (pthread_t*)malloc(sizeof(pthread_t) * max);
//		if (NULL == pool->threadIDs)
//		{
//			My_error("malloc threadIDs");
//			break;
//		}
//		memset(pool->threadIDs, 0, sizeof(ThreadPool) * max);
//		pool->minNum = min;
//		pool->maxNum = max;
//		pool->busyNum = 0;
//		pool->liveNum = min;
//		pool->exitNum = 0;
//		if (pthread_mutex_init(&pool->mutexPool, NULL) != 0 ||
//			pthread_mutex_init(&pool->mutexBusy, NULL) != 0 ||
//			pthread_cond_init(&pool->notEmpty, NULL) != 0 ||
//			pthread_cond_init(&pool->notFull, NULL) != 0)
//		{
//			My_error("nutex or condition init fail");
//			break;
//		}
//
//
//		//任务队列
//		/*pool->taskQ = (Task*)malloc(sizeof(Task) * queueSize);*/
//		pool->taskQ = (Task*)malloc(sizeof(Task) * queueSize);
//		pool->queueCapacity = queueSize;
//		pool->queueSize = 0;
//		pool->queueFront = 0;
//		pool->queueRear = 0;
//
//		pool->shutdown = 0;
//		//创建线程
//		pthread_create(&pool->manegeID, NULL, manager, pool);//第二个是属性，使用默认属性，所以为空，manage是管理者线程的任务函数，最后一个是给任务函数传 的参数
//		for (int i = 0; i < min; i++)
//		{
//			pthread_create(&pool->threadIDs[i], NULL, worker, pool);
//		}
//		return pool;
//	} while (0);
//	//资源的释放
//	if (pool && pool->threadIDs) free(pool->threadIDs);
//	if (pool && pool->taskQ) free(pool->taskQ);
//	if (pool) free(pool);
//	return NULL;
//
//}



//
//
//ThreadPool* threadPoolCreate(int min, int max, int queueSize)
//{
//	ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
//	do
//	{
//		if (pool == NULL)
//		{
//			printf("malloc threadpool fail...\n");
//			break;
//		}
//
//		pool->threadIDs = (pthread_t*)malloc(sizeof(pthread_t) * max);
//		if (pool->threadIDs == NULL)
//		{
//			printf("malloc threadIDs fail...\n");
//			break;
//		}
//		memset(pool->threadIDs, 0, sizeof(ThreadPool) * max);
//		pool->minNum = min;
//		pool->maxNum = max;
//		pool->busyNum = 0;
//		pool->liveNum = min;    // 和最小个数相等
//		pool->exitNum = 0;
//
//		if (pthread_mutex_init(&pool->mutexPool, NULL) != 0 ||
//			pthread_mutex_init(&pool->mutexBusy, NULL) != 0 ||
//			pthread_cond_init(&pool->notEmpty, NULL) != 0 ||
//			pthread_cond_init(&pool->notFull, NULL) != 0)
//		{
//			printf("mutex or condition init fail...\n");
//			break;
//		}
//
//		 //任务队列
//		pool->taskQ = (Task*)malloc(sizeof(Task) * queueSize);
//		pool->queueCapacity = queueSize;
//		pool->queueSize = 0;
//		pool->queueFront = 0;
//		pool->queueRear = 0;
//
//		pool->shutdown = 0;
//
//		// 创建线程
//		pthread_create(&pool->manegeID, NULL, manager, pool);
//		for (int i = 0; i < min; ++i)
//		{
//			pthread_create(&pool->threadIDs[i], NULL, worker, pool);
//		}
//		return pool;
//	} while (0);
//
//	// 释放资源
//	if (pool && pool->threadIDs) free(pool->threadIDs);
//	if (pool && pool->taskQ) free(pool->taskQ);
//	if (pool) free(pool);
//
//	return NULL;
//}
//
//
//void* worker(void* arg)
//{
//	ThreadPool* pool = (ThreadPool*)arg;
//	while (1)
//	{
//		pthread_mutex_lock(&pool->mutexPool);
//		while (pool->queueSize == 0 && !pool->shutdown)
//		{
//			阻塞工作线程
//			pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);
//
//			判断是不是要销毁的线程
//			if (pool->exitNum > 0)
//			{
//				pool->exitNum--;
//				if (pool->liveNum > pool->minNum)
//				{
//					pool->liveNum--;
//					pthread_mutex_unlock(&pool->mutexPool);
//					ThreadExit(pool);
//				}
//			}
//		}
//		判断线程池是否被关闭
//		if (pool->shutdown)
//		{
//			pthread_mutex_unlock(&pool->mutexPool);  //由于前面wait的时候我们给了他锁，在这里应该解锁
//			ThreadExit(pool);
//		}
//		从任务队列里面取出一个任务
//		Task task = { 0 };
//		task.function = pool->taskQ[pool->queueFront].function;
//		task.arg = pool->taskQ[pool->queueFront].arg;
//
//		移动头节点，因为任务是按着顺序拿的
//		pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;//这里使用 pool->queueCapacity取余的原因是因为，前面使用queueSize赋值了
//		pool->queueSize--;  //总的任务数需要减少
//		pthread_cond_signal(&pool->notFull);
//		pthread_mutex_unlock(&pool->mutexPool);
//
//		printf("thread %ld start working...\n", pthread_self());
//		pthread_mutex_lock(&pool->mutexBusy);
//		pool->busyNum++;
//		pthread_mutex_unlock(&pool->mutexBusy);
//		task.function(task.arg);//执行任务
//
//		释放堆内存
//		free(task.arg);
//		task.arg = NULL;
//
//		printf("thread %ld end working...\n", pthread_self());
//		pthread_mutex_lock(&pool->mutexBusy);
//		pool->busyNum--;
//		pthread_mutex_unlock(&pool->mutexBusy);
//	}
//	return NULL;
//}
//
//
//
//void* manager(void* arg)
//{
//	ThreadPool* pool = (ThreadPool*)arg;  //用void* 强制类型转换
//	while (!pool->shutdown)
//	{
//		sleep(3);//管理者的工作频率，每三秒
//
//		//取出线程池中任务的数量和当前线程的数量
//		pthread_mutex_lock(&pool->mutexPool);
//		int queueSize = pool->queueSize;
//		int liveNum = pool->liveNum;
//		pthread_mutex_unlock(&pool->mutexPool);
//
//		//取出忙的线程的个数
//		pthread_mutex_lock(&pool->mutexBusy);
//		int busyNum = pool->busyNum;
//		pthread_mutex_unlock(&pool->mutexBusy);
//
//		//添加线程
//		//当前任务 > 存活的线程数  &&  存活的线程数 < 最大的线程数
//		if (queueSize > liveNum && liveNum < pool->maxNum)
//		{
//			pthread_mutex_lock(&pool->mutexPool);
//			int counter = 0;
//			for (int  i = 0; i < pool->maxNum && counter < NUMBER &&
//				pool->liveNum < pool->maxNum; i++)  //NUMBER 是自己定义的int const
//			{
//				if (pool->threadIDs[i] == 0)
//				{
//					pthread_create(&pool->threadIDs[i], NULL, worker, pool);  //添加线程
//					counter++;
//					pool->liveNum++;  //每增加一个线程的活着的线程数++
//				}
//			}
//			pthread_mutex_unlock(&pool->mutexPool);
//		}
//
//
//		//销毁线程
//		//忙的线程*2 < 存活的线程数 && 存活的线程数 > 最小的线程数
//		if (busyNum * 2 < liveNum && liveNum > pool->minNum)
//		{
//			pthread_mutex_lock(&pool->mutexPool);
//			pool->exitNum = NUMBER;
//			pthread_mutex_unlock(&pool->mutexPool);
//			// 让工作自杀
//
//			for (int i = 0; i < NUMBER; i++)
//			{
//				pthread_cond_signal(&pool->notEmpty); //这个函数适用于唤醒上面`wait`的线程
//			}
//		}
//
//	}
//	return NULL;
//}
//
//
//void* ThreadExit(ThreadPool* pool)
//{
//	pthread_t tid = pthread_self();  //该函数用于获取线程ID
//	for (int i = 0; i < pool->maxNum; i++)
//	{
//		if (tid == pool->threadIDs[i]) //
//		{
//			pool->threadIDs = 0;
//			printf("ThreadExit(0 called , %ld exiting ...\n", tid);
//			break;
//		}
//	}
//	pthread_exit(NULL);
//
//}
//
//
//void threadPoolAdd(ThreadPool* pool, void (*func)(void*), void* arg)
//{
//	pthread_mutex_lock(&pool->mutexPool);
//	while (pool->queueCapacity == pool->queueSize && !pool->shutdown)
//	{
//		//阻塞生产者线程
//		pthread_cond_wait(&pool->notFull, &pool->mutexPool);
//	}
//	if (pool->shutdown)
//	{
//		pthread_mutex_unlock(&pool->mutexPool);
//		return;
//	}
//	//添加任务
//	//我们需要将任务添加到最后面
//	pool->taskQ[pool->queueRear].function = func;
//	pool->taskQ[pool->queueRear].arg = arg;
//	pool->queueRear = (pool->queueRear + 1) % pool->queueCapacity;
//	pool->queueSize++;
//
//
//	pthread_cond_signal(&pool->notEmpty);
//
//	pthread_mutex_unlock(&pool->mutexPool);
//
//}
//
//
//
//int threadPollBusyNum(ThreadPool* pool)
//{
//	pthread_mutex_lock(&pool->mutexBusy);
//	int busyNun = pool->busyNum;
//
//	pthread_mutex_unlock(&pool->mutexBusy);
//	return busyNun;
//}
//
//int threadPollLiveNum(ThreadPool* pool)
//{
//	pthread_mutex_lock(&pool->mutexPool);
//	int aliveNum = pool->liveNum;
//
//	pthread_mutex_unlock(&pool->mutexPool);
//	return aliveNum;
//}
//
//
//int threadPoolDestroy(ThreadPool* pool)
//{
//	if (pool == NULL)
//	{
//		return -1;
//	}
//	//关闭线程池
//	pool->shutdown = 1;
//	//阻塞回收管理者线程
//	pthread_join(pool->managerID, NULL);  //第二个参数是管理者线程返回的参数，这里没有返回值，所以值为NULL
//	//唤醒阻塞的消费者
//	//有多少个活着的线程，就需要唤醒多少次
//	for (int i = 0; i < pool->liveNum; ++i)
//	{
//		pthread_cond_signal(&pool->notEmpty);
//	}
//	//释放堆内存
//	if (pool->taskQ)
//	{
//		free(pool->taskQ);
//		pool->taskQ = NULL;
//	}
//	if (pool->threadIDs)
//	{
//		free(pool->threadIDs);
//		pool->threadIDs = NULL;
//	}	
//	free(pool);
//	pthread_mutex_destroy(&pool->mutexBusy);
//	pthread_mutex_destroy(&pool->mutexPool);
//	pthread_cond_destroy(&pool->notEmpty);
//	pthread_cond_destroy(&pool->notFull);
//
//	pool = NULL;
//
//	return 0;
//}