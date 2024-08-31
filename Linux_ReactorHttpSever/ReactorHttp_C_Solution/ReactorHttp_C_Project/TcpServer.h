//文件描述：
//      实现一个监听模块，属于TcpServer模块
//作者：钱锐
//时间：2024/1/26
//修改记录：
//      2024/1/26     新建

#pragma once
#include "ThreadPool.h"

typedef struct _LiSTENER_INFO
{
	int ListenFd;
	unsigned short ListenPort;
}LiSTENER_INFO, *PLiSTENER_INFO;

typedef struct _TCPSERVER_INFO
{
	int SubThreadNum;							//线程池内部子线程的数量
	PLiSTENER_INFO pListener_Info;				//listen相关信息
	EVENTLOOP_INFO* pMainEventLoop_Info;		//主线程事件循环模块
	THREADPOOL_INFO* pThreadPool_Info;			//线程池模块信息
}TCPSERVER_INFO, * PTCPSERVER_INFO;

/// <summary>
/// 初始化
/// </summary>
/// <param name="_ListenPort">监听端口</param>
/// <param name="_SubThreadNum">线程池子线程数量</param>
/// <returns></returns>
PTCPSERVER_INFO TcpServerInit(unsigned short _ListenPort, int _SubThreadNum);

/// <summary>
/// 启动TcpServer
/// </summary>
/// <param name="pTcpServer_Info"></param>
/// <returns></returns>
int TcpServerRun(PTCPSERVER_INFO pTcpServer_Info);


/////////////////////////////////////////内部接口/////////////////////////////////////////

/// <summary>
/// 初始化
/// </summary>
/// <param name="_ListenPort">监听端口</param>
/// <returns></returns>
PLiSTENER_INFO LinsterInit(unsigned short _ListenPort);


