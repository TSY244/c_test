#include"threadpool.h"

//工作函数
void taskFunc(void * arg)
{
	int num = *(int*)arg;
	printf("thread %ld is working , number = %d  \n",
		 pthread_self(), num);
	usleep(1000);

}

int main()
{
	//创建线程池
	ThreadPool* pool = threadPoolCreate(3, 10, 20);
	for (int i = 0; i < 100; ++i)
	{
		int* num = (int*)malloc(sizeof(int));
		*num = i + 100;
		threadPoolAdd(pool,taskFunc,num);
	}

	sleep(10);//让主线程睡眠一段时间，等待子线程任务完成

	threadPoolDestroy(pool);
	return 0;
}

