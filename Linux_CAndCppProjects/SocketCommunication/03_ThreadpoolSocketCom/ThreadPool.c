#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include"ThreadPool.h"
#include"pthread.h"

#define ONCEADDTHREADNUM 2//一次性最多添加几个线程

//任务结构体
typedef struct _THREADPOOL_TASK_INFO
{
	void (*Func)(void* _Arg);
	void* Arg;

}THREADPOOL_TASK_INFO, *PTHREADPOOL_TASK_INFO;

//线程池结构体
typedef struct _THREADPOOL_INFO
{
	//任务队列
	THREADPOOL_TASK_INFO* Task_Info;
	int QueueCapacity;					//容量
	int QueueSize;						//大小
	int QueueFront;						//队头(取数据)
	int QueueRear;						//队尾(放数据)

	pthread_t ManagerID;				//管理者线程ID
	pthread_t* WorkThreadID;			//工作的线程ID
	int Thread_MinNum;					//最小线程数量
	int Thread_MaxNum;					//最大线程数量
	int Thread_BusyNum;					//在忙的线程个数
	int	Thread_LiveNum;					//存活的线程个数
	int Thread_ExitNum;					//要销毁的线程个数

	pthread_mutex_t MutexPool;			//锁整个线程池
	pthread_mutex_t MutexBusy;			//锁Thread_BusyNum变量
	pthread_cond_t IsFull;				//任务队列是不是满了
	pthread_cond_t IsEmpty;				//任务队列是不是空了

	int ShutDown;						//是不是要销毁线程池;0--不销毁,1--销毁

}THREADPOOL_INFO, *PTHREADPOOL_INFO;

/// <summary>
/// 管理者函数
/// </summary>
/// <param name="_Arg"></param>
/// <returns></returns>
void* ManagerFunc(void* _Arg);

/// <summary>
/// 工作者函数
/// </summary>
/// <param name="_Arg"></param>
/// <returns></returns>
void* WorkFunc(void* _Arg);

/// <summary>
/// 线程退出函数
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

		//任务队列
		pThreadPool_Info->Task_Info = (THREADPOOL_TASK_INFO*)malloc(sizeof(THREADPOOL_TASK_INFO) * _Capacity);
		if (pThreadPool_Info->Task_Info == NULL)
			break;

		pThreadPool_Info->QueueCapacity = _Capacity;
		pThreadPool_Info->QueueSize = 0;
		pThreadPool_Info->QueueFront = 0;
		pThreadPool_Info->QueueRear = 0;

		//线程
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
		//每隔一段时间检测一次
		sleep(3);

		pthread_mutex_lock(&pThreadPool_Info->MutexPool);
		int nQueueSize = pThreadPool_Info->QueueSize;				//当前任务数量
		int nThread_LiveNum = pThreadPool_Info->Thread_LiveNum;		//当前存货的线程数量
		pthread_mutex_unlock(&pThreadPool_Info->MutexPool);

		pthread_mutex_lock(&pThreadPool_Info->MutexBusy);
		int nThread_BusyNum = pThreadPool_Info->Thread_BusyNum;		//当前在忙线程数量
		pthread_mutex_unlock(&pThreadPool_Info->MutexBusy);

		//添加线程
		//任务个数 > 存活的线程数 * 2 && 存活的线程数 < 最大线程数
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
		//销毁线程
		//忙的线程 * 2 < 存活线程 && 存活线程 > 最小线程
		else if (nThread_BusyNum * 2 < nThread_LiveNum && nThread_LiveNum < pThreadPool_Info->Thread_MinNum)
		{
			pthread_mutex_lock(&pThreadPool_Info->MutexPool);
			pThreadPool_Info->Thread_ExitNum = ONCEADDTHREADNUM;			//让工作者线程自杀
			pthread_mutex_unlock(&pThreadPool_Info->MutexPool);

			for (int i = 0; i < ONCEADDTHREADNUM; i++)
			{
				pthread_cond_signal(&pThreadPool_Info->IsEmpty);//唤醒wait的线程
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
		//从任务队列中取出任务
		pthread_mutex_lock(&pThreadPool_Info->MutexPool);

		//将条件变量放置于while是为了防止虚假唤醒
		while (pThreadPool_Info->QueueSize == 0 && !pThreadPool_Info->ShutDown)
		{
			//处理任务队列为空的情况
			pthread_cond_wait(&pThreadPool_Info->IsEmpty, &pThreadPool_Info->MutexPool);

			//判断是否需要销毁线程
			if (pThreadPool_Info->Thread_ExitNum > 0)
			{
				pThreadPool_Info->Thread_ExitNum--;//不能放在下面的if中，因为销毁线程如果小于最小线程是不允许销毁的

				if (pThreadPool_Info->Thread_LiveNum > pThreadPool_Info->Thread_MinNum)
				{
					pThreadPool_Info->Thread_LiveNum--;
					pthread_mutex_unlock(&pThreadPool_Info->MutexPool);
					ThreadExit(pThreadPool_Info);
				}
				
			}
		}

		//判断线程池是否被销毁了
		if (pThreadPool_Info->ShutDown)
		{
			pthread_mutex_unlock(&pThreadPool_Info->MutexPool);
			ThreadExit(pThreadPool_Info);
		}

		//取出任务
		THREADPOOL_TASK_INFO tTask_Info;
		tTask_Info.Func = pThreadPool_Info->Task_Info[pThreadPool_Info->QueueFront].Func;
		tTask_Info.Arg = pThreadPool_Info->Task_Info[pThreadPool_Info->QueueFront].Arg;
		//移动头节点
		pThreadPool_Info->QueueFront = (pThreadPool_Info->QueueFront + 1) % pThreadPool_Info->QueueCapacity;
		pThreadPool_Info->QueueSize--;

		pthread_cond_signal(&pThreadPool_Info->IsFull);//唤醒被wait的添加任务接口

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

	//将条件变量放置于while是为了防止虚假唤醒
	while (_pInfo->QueueSize == _pInfo->QueueCapacity && !_pInfo->ShutDown)
	{
		pthread_cond_wait(&_pInfo->IsFull, &_pInfo->MutexPool);
	}

	if (_pInfo->ShutDown == 1)
	{
		pthread_mutex_unlock(&_pInfo->MutexPool);
		return;
	}

	//添加任务
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

	//销毁
	pthread_mutex_destroy(&_pInfo->MutexPool);
	pthread_mutex_destroy(&_pInfo->MutexBusy);
	pthread_cond_destroy(&_pInfo->IsEmpty);
	pthread_cond_destroy(&_pInfo->IsFull);

	//释放内存
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
	pthread_t thID = pthread_self();//获取当前线程的ID

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
