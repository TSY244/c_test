

//
//#ifndef _THREADPOOL_H
//#define _THREADPOOL_H
//
//
//#include<pthread.h>
//#include<stdio.h>
//#include<stdlib.h>
////#include<unistd.h>
//#include<string.h>
////
//typedef struct ThreadPool ThreadPool;
//// �����̳߳ز���ʼ��
//ThreadPool* threadPoolCreate(int min, int max, int queueSize);
//
//// �����̳߳�
//int threadPoolDestroy(ThreadPool* pool);
//
//// ���̳߳��������
//void threadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg);
//
//// ��ȡ�̳߳��й������̵߳ĸ���
//int threadPoolBusyNum(ThreadPool* pool);
//
//// ��ȡ�̳߳��л��ŵ��̵߳ĸ���
//int threadPoolAliveNum(ThreadPool* pool);
//
////////////////////////
//// �������߳�(�������߳�)������
//void* worker(void* arg);
//// �������߳�������
//void* manager(void* arg);
//// �����߳��˳�
//void threadExit(ThreadPool* pool);
//#endif  // _THREADPOOL_H




#ifndef _THREADPOLL_H
#define _THREADPOLL_H

#pragma once
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
//#include<unistd.h>
#include<string.h>


#define My_error(error) printf("[ LINE %d ] is failed ,because %s",__LINE__,error);




//�����̳߳�
typedef struct ThreadPool ThreadPool;
ThreadPool* threadPoolCreate(int min, int max,int queueSize);
 
//�����̳߳�
int threadPoolDestroy(ThreadPool* pool);

//���̳߳���������
void threadPoolAdd(ThreadPool* pool, void (*func)(void*), void* arg);

//��ȡ�ж��ٸ��������߳�
int threadPoolBusyNum(ThreadPool* pool);

//��ȡ���ŵ��߳�
int threadPoolLiveNum(ThreadPool* pool);


///////
void* worker(void* arg);
void* manager(void* arg);
void* ThreadExit(ThreadPool* pool);
///////

#endif // !_THREADPOLL_H



//
//
