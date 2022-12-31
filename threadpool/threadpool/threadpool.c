
#include"threadpool.h"


const int NUMBER = 2;


// ����ṹ��
typedef struct Task
{
    void (*function)(void* arg);
    void* arg;
}Task;


// �̳߳ؽṹ��
struct ThreadPool
{
    // �������
    Task* taskQ;
    int queueCapacity;  // ����
    int queueSize;      // ��ǰ�������
    int queueFront;     // ��ͷ -> ȡ����
    int queueRear;      // ��β -> ������

    pthread_t managerID;    // �������߳�ID
    pthread_t* threadIDs;   // �������߳�ID
    int minNum;             // ��С�߳�����
    int maxNum;             // ����߳�����
    int busyNum;            // æ���̵߳ĸ���
    int liveNum;            // �����̵߳ĸ���
    int exitNum;            // Ҫ���ٵ��̸߳���
    pthread_mutex_t mutexPool;  // ���������̳߳�
    pthread_mutex_t mutexBusy;  // ��busyNum����
    pthread_cond_t notFull;     // ��������ǲ�������
    pthread_cond_t notEmpty;    // ��������ǲ��ǿ���

    int shutdown;           // �ǲ���Ҫ�����̳߳�, ����Ϊ1, ������Ϊ0
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
        pool->liveNum = min;    // ����С�������
        pool->exitNum = 0;

        if (pthread_mutex_init(&pool->mutexPool, NULL) != 0 ||
            pthread_mutex_init(&pool->mutexBusy, NULL) != 0 ||
            pthread_cond_init(&pool->notEmpty, NULL) != 0 ||
            pthread_cond_init(&pool->notFull, NULL) != 0)
        {
            printf("mutex or condition init fail...\n");
            break;
        }

        // �������
        pool->taskQ = (Task*)malloc(sizeof(Task) * queueSize);
        pool->queueCapacity = queueSize;
        pool->queueSize = 0;
        pool->queueFront = 0;
        pool->queueRear = 0;

        pool->shutdown = 0;

        // �����߳�
        pthread_create(&pool->managerID, NULL, manager, pool);
        for (int i = 0; i < min; ++i)
        {
            pthread_create(&pool->threadIDs[i], NULL, worker, pool);
        }
        return pool;
    } while (0);

    // �ͷ���Դ
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

    // �ر��̳߳�
    pool->shutdown = 1;
    // �������չ������߳�
    pthread_join(pool->managerID, NULL);
    // �����������������߳�
    for (int i = 0; i < pool->liveNum; ++i)
    {
        pthread_cond_signal(&pool->notEmpty);
    }
    // �ͷŶ��ڴ�
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
        // �����������߳�
        pthread_cond_wait(&pool->notFull, &pool->mutexPool);
    }
    if (pool->shutdown)
    {
        pthread_mutex_unlock(&pool->mutexPool);
        return;
    }
    // �������
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
        // ��ǰ��������Ƿ�Ϊ��
        while (pool->queueSize == 0 && !pool->shutdown)
        {
            // ���������߳�
            pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);

            // �ж��ǲ���Ҫ�����߳�
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

        // �ж��̳߳��Ƿ񱻹ر���
        if (pool->shutdown)
        {
            pthread_mutex_unlock(&pool->mutexPool);
            threadExit(pool);
        }

        // �����������ȡ��һ������
        Task task;
        task.function = pool->taskQ[pool->queueFront].function;
        task.arg = pool->taskQ[pool->queueFront].arg;
        // �ƶ�ͷ���
        pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;
        pool->queueSize--;
        // ����
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
        // ÿ��3s���һ��
        sleep(3);

        // ȡ���̳߳�������������͵�ǰ�̵߳�����
        pthread_mutex_lock(&pool->mutexPool);
        int queueSize = pool->queueSize;
        int liveNum = pool->liveNum;
        pthread_mutex_unlock(&pool->mutexPool);

        // ȡ��æ���̵߳�����
        pthread_mutex_lock(&pool->mutexBusy);
        int busyNum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);

        // ����߳�
        // ����ĸ���>�����̸߳��� && �����߳���<����߳���
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
        // �����߳�
        // æ���߳�*2 < �����߳��� && �����߳�>��С�߳���
        if (busyNum * 2 < liveNum && liveNum > pool->minNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            pool->exitNum = NUMBER;
            pthread_mutex_unlock(&pool->mutexPool);
            // �ù������߳���ɱ
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
////����ṹ��
//typedef struct Task
//{
//	void (*function)(void* arg);
//	void* arg;
//}Task;
//
//
//
////�̳߳ؽṹ��
//struct ThreadPool
//{
//	Task* taskQ;
//	int queueCapacity;  //����
//	int queueSize;      //��ǰ����ĸ���
//	int queueFront;     //��ͷ ->ȡ����
//	int queueRear;      //��β ->������
//
//	pthread_t manegeID;    //������ID   pthread_t  �޷��ų�����
//	pthread_t* threadIDs;  //�������߳�ID
//	int minNum;            //��С�߳���
//	int maxNum;            //����߳���
//	int busyNum;           //æ���߳���
//	int liveNum;           //���ŵ��߳���
//	int exitNum;           //ɱ�����߳���
//	pthread_mutex_t mutexPool;   //�������̳߳�   pthread_mutex_t  ����������
//	pthread_mutex_t mutexBusy;   //���������߳�
//	pthread_cond_t notEmpty;   //�ж��ǲ��ǿ���   pthread_cond_t  ������ 
//	pthread_cond_t notFull;    //�ж��ǲ�������
//
//
//	int shutdown;          //�ǲ��������̳߳أ�����Ϊ1��������Ϊ0
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
//		//�������
//		/*pool->taskQ = (Task*)malloc(sizeof(Task) * queueSize);*/
//		pool->taskQ = (Task*)malloc(sizeof(Task) * queueSize);
//		pool->queueCapacity = queueSize;
//		pool->queueSize = 0;
//		pool->queueFront = 0;
//		pool->queueRear = 0;
//
//		pool->shutdown = 0;
//		//�����߳�
//		pthread_create(&pool->manegeID, NULL, manager, pool);//�ڶ��������ԣ�ʹ��Ĭ�����ԣ�����Ϊ�գ�manage�ǹ������̵߳������������һ���Ǹ��������� �Ĳ���
//		for (int i = 0; i < min; i++)
//		{
//			pthread_create(&pool->threadIDs[i], NULL, worker, pool);
//		}
//		return pool;
//	} while (0);
//	//��Դ���ͷ�
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
//		pool->liveNum = min;    // ����С�������
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
//		 //�������
//		pool->taskQ = (Task*)malloc(sizeof(Task) * queueSize);
//		pool->queueCapacity = queueSize;
//		pool->queueSize = 0;
//		pool->queueFront = 0;
//		pool->queueRear = 0;
//
//		pool->shutdown = 0;
//
//		// �����߳�
//		pthread_create(&pool->manegeID, NULL, manager, pool);
//		for (int i = 0; i < min; ++i)
//		{
//			pthread_create(&pool->threadIDs[i], NULL, worker, pool);
//		}
//		return pool;
//	} while (0);
//
//	// �ͷ���Դ
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
//			���������߳�
//			pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);
//
//			�ж��ǲ���Ҫ���ٵ��߳�
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
//		�ж��̳߳��Ƿ񱻹ر�
//		if (pool->shutdown)
//		{
//			pthread_mutex_unlock(&pool->mutexPool);  //����ǰ��wait��ʱ�����Ǹ���������������Ӧ�ý���
//			ThreadExit(pool);
//		}
//		�������������ȡ��һ������
//		Task task = { 0 };
//		task.function = pool->taskQ[pool->queueFront].function;
//		task.arg = pool->taskQ[pool->queueFront].arg;
//
//		�ƶ�ͷ�ڵ㣬��Ϊ�����ǰ���˳���õ�
//		pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;//����ʹ�� pool->queueCapacityȡ���ԭ������Ϊ��ǰ��ʹ��queueSize��ֵ��
//		pool->queueSize--;  //�ܵ���������Ҫ����
//		pthread_cond_signal(&pool->notFull);
//		pthread_mutex_unlock(&pool->mutexPool);
//
//		printf("thread %ld start working...\n", pthread_self());
//		pthread_mutex_lock(&pool->mutexBusy);
//		pool->busyNum++;
//		pthread_mutex_unlock(&pool->mutexBusy);
//		task.function(task.arg);//ִ������
//
//		�ͷŶ��ڴ�
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
//	ThreadPool* pool = (ThreadPool*)arg;  //��void* ǿ������ת��
//	while (!pool->shutdown)
//	{
//		sleep(3);//�����ߵĹ���Ƶ�ʣ�ÿ����
//
//		//ȡ���̳߳�������������͵�ǰ�̵߳�����
//		pthread_mutex_lock(&pool->mutexPool);
//		int queueSize = pool->queueSize;
//		int liveNum = pool->liveNum;
//		pthread_mutex_unlock(&pool->mutexPool);
//
//		//ȡ��æ���̵߳ĸ���
//		pthread_mutex_lock(&pool->mutexBusy);
//		int busyNum = pool->busyNum;
//		pthread_mutex_unlock(&pool->mutexBusy);
//
//		//����߳�
//		//��ǰ���� > �����߳���  &&  �����߳��� < �����߳���
//		if (queueSize > liveNum && liveNum < pool->maxNum)
//		{
//			pthread_mutex_lock(&pool->mutexPool);
//			int counter = 0;
//			for (int  i = 0; i < pool->maxNum && counter < NUMBER &&
//				pool->liveNum < pool->maxNum; i++)  //NUMBER ���Լ������int const
//			{
//				if (pool->threadIDs[i] == 0)
//				{
//					pthread_create(&pool->threadIDs[i], NULL, worker, pool);  //����߳�
//					counter++;
//					pool->liveNum++;  //ÿ����һ���̵߳Ļ��ŵ��߳���++
//				}
//			}
//			pthread_mutex_unlock(&pool->mutexPool);
//		}
//
//
//		//�����߳�
//		//æ���߳�*2 < �����߳��� && �����߳��� > ��С���߳���
//		if (busyNum * 2 < liveNum && liveNum > pool->minNum)
//		{
//			pthread_mutex_lock(&pool->mutexPool);
//			pool->exitNum = NUMBER;
//			pthread_mutex_unlock(&pool->mutexPool);
//			// �ù�����ɱ
//
//			for (int i = 0; i < NUMBER; i++)
//			{
//				pthread_cond_signal(&pool->notEmpty); //������������ڻ�������`wait`���߳�
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
//	pthread_t tid = pthread_self();  //�ú������ڻ�ȡ�߳�ID
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
//		//�����������߳�
//		pthread_cond_wait(&pool->notFull, &pool->mutexPool);
//	}
//	if (pool->shutdown)
//	{
//		pthread_mutex_unlock(&pool->mutexPool);
//		return;
//	}
//	//�������
//	//������Ҫ��������ӵ������
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
//	//�ر��̳߳�
//	pool->shutdown = 1;
//	//�������չ������߳�
//	pthread_join(pool->managerID, NULL);  //�ڶ��������ǹ������̷߳��صĲ���������û�з���ֵ������ֵΪNULL
//	//����������������
//	//�ж��ٸ����ŵ��̣߳�����Ҫ���Ѷ��ٴ�
//	for (int i = 0; i < pool->liveNum; ++i)
//	{
//		pthread_cond_signal(&pool->notEmpty);
//	}
//	//�ͷŶ��ڴ�
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