#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include"ThreadPool.h"
#include"pthread.h"

#define ONCEADDTHREADNUM 2//һ���������Ӽ����߳�

//����ṹ��
typedef struct _THREADPOOL_TASK_INFO
{
	void (*Func)(void* _Arg);
	void* Arg;

}THREADPOOL_TASK_INFO, *PTHREADPOOL_TASK_INFO;

//�̳߳ؽṹ��
typedef struct _THREADPOOL_INFO
{
	//�������
	THREADPOOL_TASK_INFO* Task_Info;
	int QueueCapacity;					//����
	int QueueSize;						//��С
	int QueueFront;						//��ͷ(ȡ����)
	int QueueRear;						//��β(������)

	pthread_t ManagerID;				//�������߳�ID
	pthread_t* WorkThreadID;			//�������߳�ID
	int Thread_MinNum;					//��С�߳�����
	int Thread_MaxNum;					//����߳�����
	int Thread_BusyNum;					//��æ���̸߳���
	int	Thread_LiveNum;					//�����̸߳���
	int Thread_ExitNum;					//Ҫ���ٵ��̸߳���

	pthread_mutex_t MutexPool;			//�������̳߳�
	pthread_mutex_t MutexBusy;			//��Thread_BusyNum����
	pthread_cond_t IsFull;				//��������ǲ�������
	pthread_cond_t IsEmpty;				//��������ǲ��ǿ���

	int ShutDown;						//�ǲ���Ҫ�����̳߳�;0--������,1--����

}THREADPOOL_INFO, *PTHREADPOOL_INFO;

/// <summary>
/// �����ߺ���
/// </summary>
/// <param name="_Arg"></param>
/// <returns></returns>
void* ManagerFunc(void* _Arg);

/// <summary>
/// �����ߺ���
/// </summary>
/// <param name="_Arg"></param>
/// <returns></returns>
void* WorkFunc(void* _Arg);

/// <summary>
/// �߳��˳�����
/// </summary>
/// <param name="_pInfo"></param>
void ThreadExit(THREADPOOL_INFO* _pInfo);

THREADPOOL_INFO* ThreadPool_Create(int _MinNum, int _MaxNum, int _Capacity)
{
	PTHREADPOOL_INFO pThreadPool_Info = (PTHREADPOOL_INFO)malloc(sizeof(THREADPOOL_INFO));
	
	do
	{
		if (pThreadPool_Info == NULL)
			break;

		//�������
		pThreadPool_Info->Task_Info = (THREADPOOL_TASK_INFO*)malloc(sizeof(THREADPOOL_TASK_INFO) * _Capacity);
		if (pThreadPool_Info->Task_Info == NULL)
			break;

		pThreadPool_Info->QueueCapacity = _Capacity;
		pThreadPool_Info->QueueSize = 0;
		pThreadPool_Info->QueueFront = 0;
		pThreadPool_Info->QueueRear = 0;

		//�߳�
		pThreadPool_Info->WorkThreadID = (pthread_t*)malloc(sizeof(pthread_t) * _MinNum);
		if (pThreadPool_Info->WorkThreadID == NULL)
			break;

		pThreadPool_Info->ManagerID = 0;
		memset(pThreadPool_Info->WorkThreadID, 0, sizeof(pthread_t) * _MinNum);
		pThreadPool_Info->Thread_MinNum = _MinNum;
		pThreadPool_Info->Thread_MaxNum = _MaxNum;
		pThreadPool_Info->Thread_BusyNum = 0;
		pThreadPool_Info->Thread_LiveNum = _MinNum;
		pThreadPool_Info->Thread_ExitNum = 0;

		pthread_create(&(pThreadPool_Info->ManagerID), NULL, ManagerFunc, pThreadPool_Info);
		if (pThreadPool_Info->ManagerID == 0)
			break;

		for (int i = 0; i < pThreadPool_Info->Thread_LiveNum; i++)
		{
			pthread_create(pThreadPool_Info->WorkThreadID + i, NULL, WorkFunc, pThreadPool_Info);

			if (pThreadPool_Info->WorkThreadID + i == 0)
				break;
		}

		if (pthread_mutex_init(&pThreadPool_Info->MutexPool, 0) != 0 || pthread_mutex_init(&pThreadPool_Info->MutexBusy, 0) != 0
			|| pthread_cond_init(&pThreadPool_Info->IsFull, 0) != 0 || pthread_cond_init(&pThreadPool_Info->IsEmpty, 0) != 0)
			break;

		pThreadPool_Info->ShutDown = 0;
	} while (0);

	if (pThreadPool_Info->Task_Info == NULL) free(pThreadPool_Info->Task_Info);
	if (pThreadPool_Info->WorkThreadID == NULL) free(pThreadPool_Info->WorkThreadID);
	if (pThreadPool_Info == NULL) free(pThreadPool_Info);

	return pThreadPool_Info;
}

void* ManagerFunc(void* _Arg)
{
	PTHREADPOOL_INFO pThreadPool_Info = (PTHREADPOOL_INFO)_Arg;

	while (!pThreadPool_Info->ShutDown)
	{
		//ÿ��һ��ʱ����һ��
		sleep(3);

		pthread_mutex_lock(&pThreadPool_Info->MutexPool);
		int nQueueSize = pThreadPool_Info->QueueSize;				//��ǰ��������
		int nThread_LiveNum = pThreadPool_Info->Thread_LiveNum;		//��ǰ������߳�����
		pthread_mutex_unlock(&pThreadPool_Info->MutexPool);

		pthread_mutex_lock(&pThreadPool_Info->MutexBusy);
		int nThread_BusyNum = pThreadPool_Info->Thread_BusyNum;		//��ǰ��æ�߳�����
		pthread_mutex_unlock(&pThreadPool_Info->MutexBusy);

		//����߳�
		//������� > �����߳��� * 2 && �����߳��� < ����߳���
		if (nQueueSize > nThread_LiveNum * 2 && nThread_LiveNum < pThreadPool_Info->Thread_MaxNum)
		{
			int nAddThreadNum = 0;

			pthread_mutex_lock(&pThreadPool_Info->MutexPool);
			for (int i = 0; i < pThreadPool_Info->Thread_MaxNum && nAddThreadNum < ONCEADDTHREADNUM && 
				pThreadPool_Info->Thread_LiveNum < pThreadPool_Info->Thread_MaxNum; i++)
			{
				if (pThreadPool_Info->WorkThreadID[i] == 0)
				{
					pthread_create(&pThreadPool_Info->WorkThreadID[i], NULL, WorkFunc, pThreadPool_Info);
					nAddThreadNum++;
					pThreadPool_Info->Thread_LiveNum++;
				}
			}
			pthread_mutex_unlock(&pThreadPool_Info->MutexPool);
		}
		//�����߳�
		//æ���߳� * 2 < ����߳� && ����߳� > ��С�߳�
		else if (nThread_BusyNum * 2 < nThread_LiveNum && nThread_LiveNum < pThreadPool_Info->Thread_MinNum)
		{
			pthread_mutex_lock(&pThreadPool_Info->MutexPool);
			pThreadPool_Info->Thread_ExitNum = ONCEADDTHREADNUM;			//�ù������߳���ɱ
			pthread_mutex_unlock(&pThreadPool_Info->MutexPool);

			for (int i = 0; i < ONCEADDTHREADNUM; i++)
			{
				pthread_cond_signal(&pThreadPool_Info->IsEmpty);//����wait���߳�
			}
		}
	}

	return NULL;
}

void* WorkFunc(void* _Arg)
{
	PTHREADPOOL_INFO pThreadPool_Info = (PTHREADPOOL_INFO)_Arg;

	while (1)
	{
		//�����������ȡ������
		pthread_mutex_lock(&pThreadPool_Info->MutexPool);

		//����������������while��Ϊ�˷�ֹ��ٻ���
		while (pThreadPool_Info->QueueSize == 0 && !pThreadPool_Info->ShutDown)
		{
			//�����������Ϊ�յ����
			pthread_cond_wait(&pThreadPool_Info->IsEmpty, &pThreadPool_Info->MutexPool);

			//�ж��Ƿ���Ҫ�����߳�
			if (pThreadPool_Info->Thread_ExitNum > 0)
			{
				pThreadPool_Info->Thread_ExitNum--;//���ܷ��������if�У���Ϊ�����߳����С����С�߳��ǲ��������ٵ�

				if (pThreadPool_Info->Thread_LiveNum > pThreadPool_Info->Thread_MinNum)
				{
					pThreadPool_Info->Thread_LiveNum--;
					pthread_mutex_unlock(&pThreadPool_Info->MutexPool);
					ThreadExit(pThreadPool_Info);
				}
				
			}
		}

		//�ж��̳߳��Ƿ�������
		if (pThreadPool_Info->ShutDown)
		{
			pthread_mutex_unlock(&pThreadPool_Info->MutexPool);
			ThreadExit(pThreadPool_Info);
		}

		//ȡ������
		THREADPOOL_TASK_INFO tTask_Info;
		tTask_Info.Func = pThreadPool_Info->Task_Info[pThreadPool_Info->QueueFront].Func;
		tTask_Info.Arg = pThreadPool_Info->Task_Info[pThreadPool_Info->QueueFront].Arg;
		//�ƶ�ͷ�ڵ�
		pThreadPool_Info->QueueFront = (pThreadPool_Info->QueueFront + 1) % pThreadPool_Info->QueueCapacity;
		pThreadPool_Info->QueueSize--;

		pthread_cond_signal(&pThreadPool_Info->IsFull);//���ѱ�wait���������ӿ�

		pthread_mutex_unlock(&pThreadPool_Info->MutexPool);

		printf("Thread start working...\n");

		pthread_mutex_lock(&pThreadPool_Info->MutexBusy);
		pThreadPool_Info->Thread_BusyNum++;
		pthread_mutex_unlock(&pThreadPool_Info->MutexBusy);

		tTask_Info.Func(tTask_Info.Arg);

		pthread_mutex_lock(&pThreadPool_Info->MutexBusy);
		pThreadPool_Info->Thread_BusyNum--;
		pthread_mutex_unlock(&pThreadPool_Info->MutexBusy);

		printf("Thread end working...\n");
	}

	return NULL;
}

void ThreadPoolAdd(THREADPOOL_INFO* _pInfo, void(*Func)(void*), void* _Arg)
{
	pthread_mutex_lock(&_pInfo->MutexPool);

	//����������������while��Ϊ�˷�ֹ��ٻ���
	while (_pInfo->QueueSize == _pInfo->QueueCapacity && !_pInfo->ShutDown)
	{
		pthread_cond_wait(&_pInfo->IsFull, &_pInfo->MutexPool);
	}

	if (_pInfo->ShutDown == 1)
	{
		pthread_mutex_unlock(&_pInfo->MutexPool);
		return;
	}

	//�������
	_pInfo->Task_Info[_pInfo->QueueRear].Func = Func;
	_pInfo->Task_Info[_pInfo->QueueRear].Arg = _Arg;
	_pInfo->QueueSize++;

	_pInfo->QueueRear = (_pInfo->QueueRear + 1) % _pInfo->QueueCapacity;

	pthread_cond_signal(&_pInfo->IsEmpty);

	pthread_mutex_unlock(&_pInfo->MutexPool);
}

int GetThreadPool_BusyThreadNum(THREADPOOL_INFO* _pInfo)
{
	pthread_mutex_lock(&_pInfo->MutexPool);
	int nBusyNum = _pInfo->Thread_BusyNum;
	pthread_mutex_unlock(&_pInfo->MutexPool);
	return nBusyNum;
}

int GetThreadPool_AliveThreadNum(THREADPOOL_INFO* _pInfo)
{
	pthread_mutex_lock(&_pInfo->MutexPool);
	int nAliveNum = _pInfo->Thread_LiveNum;
	pthread_mutex_unlock(&_pInfo->MutexPool);
	return nAliveNum;
}

int ThreadPool_Destroy(THREADPOOL_INFO* _pInfo)
{
	if (_pInfo == NULL)
	{
		return -1;
	}

	_pInfo->ShutDown = 1;
	pthread_join(_pInfo->ManagerID, NULL);

	for (int i = 0; i < _pInfo->Thread_LiveNum; i++)
	{
		pthread_cond_signal(&_pInfo->IsEmpty);
	}

	//����
	pthread_mutex_destroy(&_pInfo->MutexPool);
	pthread_mutex_destroy(&_pInfo->MutexBusy);
	pthread_cond_destroy(&_pInfo->IsEmpty);
	pthread_cond_destroy(&_pInfo->IsFull);

	//�ͷ��ڴ�
	if (_pInfo->WorkThreadID)
		free(_pInfo->WorkThreadID);
	if (_pInfo->Task_Info)
		free(_pInfo->Task_Info);
	free(_pInfo);

	printf("ThreadPool_Destroy called, destroying...\n");
	return 1;
}

void ThreadExit(THREADPOOL_INFO* _pInfo)
{
	pthread_t thID = pthread_self();//��ȡ��ǰ�̵߳�ID

	for (int i = 0; i < _pInfo->Thread_MaxNum; i++)
	{
		if (thID == _pInfo->WorkThreadID[i])
		{
			_pInfo->WorkThreadID[i] = 0;
			pthread_exit(NULL);

			printf("ThreadExit called, %ld exiting...\n", thID);
			break;
		}
	}
}
