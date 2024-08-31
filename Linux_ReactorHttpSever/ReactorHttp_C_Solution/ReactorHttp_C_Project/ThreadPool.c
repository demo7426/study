#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "ThreadPool.h"

PTHREADPOOL_INFO ThreadPoolInit(PEVENTLOOP_INFO _pMainLoop_Info, int _SubThreadNum)
{
	PTHREADPOOL_INFO ptThreadPool_Info = (PTHREADPOOL_INFO)malloc(sizeof(THREADPOOL_INFO));
	if (ptThreadPool_Info == NULL)
		return NULL;

	ptThreadPool_Info->SubThreadNum = _SubThreadNum;
	ptThreadPool_Info->SubThreadIndex = 0;
	ptThreadPool_Info->IsStart = false;
	ptThreadPool_Info->pMainEventLoop_Info = _pMainLoop_Info;
	ptThreadPool_Info->pWorkThread_Info = (PWORKTHREAD_INFO)malloc(sizeof(WORKTHREAD_INFO) * _SubThreadNum);
	if (ptThreadPool_Info->pWorkThread_Info == NULL)
	{
		free(ptThreadPool_Info);
		return NULL;
	}

	return ptThreadPool_Info;
}

void ThreadPoolRun(PTHREADPOOL_INFO _pThreadPool_Info)
{
	assert(_pThreadPool_Info && !_pThreadPool_Info->IsStart);
	if (_pThreadPool_Info->pMainEventLoop_Info->ThreadId != pthread_self())		//保证必须是主线程调用该函数
	{
		exit(0);
	}

	_pThreadPool_Info->IsStart = true;
	for (int i = 0; i < _pThreadPool_Info->SubThreadNum; i++)
	{
		WorkThreadInit(&(_pThreadPool_Info->pWorkThread_Info[i]), i);
		WorkThreadRun(&(_pThreadPool_Info->pWorkThread_Info[i]));
	}
}

PEVENTLOOP_INFO GetEventLoopObj(PTHREADPOOL_INFO _pThreadPool_Info)
{
	assert(_pThreadPool_Info && _pThreadPool_Info->IsStart);
	if (_pThreadPool_Info->pMainEventLoop_Info->ThreadId != pthread_self())		//保证必须是主线程调用该函数
	{
		exit(0);
	}

	PEVENTLOOP_INFO ptEventLoop_Info = _pThreadPool_Info->pMainEventLoop_Info;	//如果没有子线程，则返回主线程的反应堆实例
	if (_pThreadPool_Info->SubThreadNum > 0)
	{
		ptEventLoop_Info = _pThreadPool_Info->pWorkThread_Info[_pThreadPool_Info->SubThreadIndex].pEventLoop_Info;

		_pThreadPool_Info->SubThreadIndex++;
		_pThreadPool_Info->SubThreadIndex %= _pThreadPool_Info->SubThreadNum;
	}

	return ptEventLoop_Info;
}
