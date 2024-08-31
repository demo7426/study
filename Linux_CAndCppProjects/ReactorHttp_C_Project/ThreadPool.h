//文件描述：
//      实现一个线程池模块（线程池中最少有1个线程，因为必须存在一个主线程）
//作者：钱锐
//时间：2024/1/24
//修改记录：
//      2024/1/24     新建
#pragma once
#include <stdbool.h>

#include "WorkThread.h"

typedef struct _THREADPOOL_INFO
{
	bool IsStart;								//线程池是否启动;true--已启动,false--未启动
	int SubThreadNum;							//线程池内部子线程数量
	int SubThreadIndex;							//子线程索引

	PEVENTLOOP_INFO pMainEventLoop_Info;		//主线程事件循环模块
	PWORKTHREAD_INFO pWorkThread_Info;			//子线程工作者线程起始地址
}THREADPOOL_INFO, *PTHREADPOOL_INFO;

/// <summary>
/// 线程池初始化
/// </summary>
/// <param name="_pMainLoop_Info">主线程事件循环模块</param>
/// <param name="_SubThreadNum">待创建的子线程数量</param>
/// <returns></returns>
PTHREADPOOL_INFO ThreadPoolInit(PEVENTLOOP_INFO _pMainLoop_Info, int _SubThreadNum);

// 线程池启动
void ThreadPoolRun(PTHREADPOOL_INFO _pThreadPool_Info);

//获取反应堆实例指针，用于向其事件循环内部任务队列添加子任务
PEVENTLOOP_INFO GetEventLoopObj(PTHREADPOOL_INFO _pThreadPool_Info);
