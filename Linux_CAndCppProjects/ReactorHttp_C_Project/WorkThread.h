//文件描述：
//      实现一个工作者线程模块
//作者：钱锐
//时间：2024/1/24
//修改记录：
//      2024/1/24     新建
#pragma once 
#include "EventLoop.h"

typedef struct _WORKTHREAD_INFO
{
	PEVENTLOOP_INFO pEventLoop_Info;

	pthread_t ThreadId;					//线程id
	char ThreadName[32];				//线程名称
	pthread_mutex_t Mutex;				
	pthread_cond_t Cond;
}WORKTHREAD_INFO, *PWORKTHREAD_INFO;


//初始化
int WorkThreadInit(PWORKTHREAD_INFO pWorkThread_Info, int _Index);

//运行
void WorkThreadRun(PWORKTHREAD_INFO pWorkThread_Info);