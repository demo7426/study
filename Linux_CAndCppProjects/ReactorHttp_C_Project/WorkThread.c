//文件描述：
//      实现一个工作者线程模块
//作者：钱锐
//时间：2024/1/24
//修改记录：
//      2024/1/24     新建
#include <stdio.h>

#include "WorkThread.h"

int WorkThreadInit(PWORKTHREAD_INFO pWorkThread_Info, int _SerialNum)
{
	pWorkThread_Info->ThreadId = 0;
	sprintf(pWorkThread_Info->ThreadName, "Subthread-%d", _SerialNum);
	pWorkThread_Info->pEventLoop_Info = NULL;

	pthread_mutex_init(&pWorkThread_Info->Mutex, NULL);
	pthread_cond_init(&pWorkThread_Info->Cond, NULL);
	return 0;
}

void* SubThreadRunning(void* _Arg)
{
	PWORKTHREAD_INFO ptWorkThread_Info = (PWORKTHREAD_INFO)_Arg;

	pthread_mutex_lock(&ptWorkThread_Info->Mutex);
	ptWorkThread_Info->pEventLoop_Info = EventLoopInitEx(ptWorkThread_Info->ThreadName);
	pthread_mutex_unlock(&ptWorkThread_Info->Mutex);
	pthread_cond_signal(&ptWorkThread_Info->Cond);
	
	EventLoopRun(ptWorkThread_Info->pEventLoop_Info);

	return NULL;
}

void WorkThreadRun(PWORKTHREAD_INFO pWorkThread_Info)
{
	pthread_create(&pWorkThread_Info->ThreadId, NULL, SubThreadRunning, pWorkThread_Info);

	//保证子线程初始化EventLoop成功，防止误操作到空指针导致程序崩溃
	pthread_mutex_lock(&pWorkThread_Info->Mutex);
	while (pWorkThread_Info->pEventLoop_Info == NULL)
	{
		pthread_cond_wait(&pWorkThread_Info->Cond, &pWorkThread_Info->Mutex);
	}
	pthread_mutex_unlock(&pWorkThread_Info->Mutex);
}
