#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "TcpServer.h"
#include "TcpConnection.h"

PTCPSERVER_INFO TcpServerInit(unsigned short _ListenPort, int _SubThreadNum)
{
	PTCPSERVER_INFO ptTcpServer_Info = (PTCPSERVER_INFO)malloc(sizeof(TCPSERVER_INFO));
	if (ptTcpServer_Info == NULL)
		return NULL;

	ptTcpServer_Info->pListener_Info = LinsterInit(_ListenPort);
	if (ptTcpServer_Info->pListener_Info == NULL)
	{
		free(ptTcpServer_Info);
		ptTcpServer_Info = NULL;
		return NULL;
	}

	ptTcpServer_Info->pMainEventLoop_Info = EventLoopInit();
	ptTcpServer_Info->pThreadPool_Info = ThreadPoolInit(ptTcpServer_Info->pMainEventLoop_Info, _SubThreadNum);
	ptTcpServer_Info->SubThreadNum = _SubThreadNum;

	return ptTcpServer_Info;
}

static int AcceptReadCallBack(void* _Arg)
{
	PTCPSERVER_INFO ptTcpServer_Info = (PTCPSERVER_INFO)_Arg;

	int nFd = accept(ptTcpServer_Info->pListener_Info->ListenFd, NULL, NULL);
	if (nFd <= 0)
		return -1;

	//将已经建立好连接的客户端文件描述符，递交给子线程处理（主线程只负责连接客户端）
	PEVENTLOOP_INFO ptEventLoop_Info = GetEventLoopObj(ptTcpServer_Info->pThreadPool_Info);
	TcpConnectionInit(nFd, ptEventLoop_Info);
	return 0;
}

int TcpServerRun(PTCPSERVER_INFO pTcpServer_Info)
{
	//启动线程池
	ThreadPoolRun(pTcpServer_Info->pThreadPool_Info);

	//添加主线程事件模块监听任务
	PCHANNEL_INFO ptChannel_Info = ChannelInit(pTcpServer_Info->pListener_Info->ListenFd, READEVENT, AcceptReadCallBack, NULL, NULL, pTcpServer_Info);
	EventLoopAddTask(pTcpServer_Info->pMainEventLoop_Info, ptChannel_Info, ADD);

	//启动主线程事件循环模块
	EventLoopRun(pTcpServer_Info->pMainEventLoop_Info);

	return 0;
}

PLiSTENER_INFO LinsterInit(unsigned short _ListenPort)
{
	PLiSTENER_INFO ptLitener_Info = (PLiSTENER_INFO)malloc(sizeof(LiSTENER_INFO));
	if (ptLitener_Info == NULL)
		return NULL;

	//创建socket套接字
	int nFd = socket(AF_INET, SOCK_STREAM, 0);
	if (nFd == -1)
	{
		perror("socket failed.");
		return NULL;
	}

	//设置端口复用
	int nOptVal = 1;
	int nRet = setsockopt(nFd, SOL_SOCKET, SO_REUSEADDR, &nOptVal, sizeof nOptVal);
	if (nRet == -1)
	{
		perror("setsockopt failed.");
		return NULL;
	}

	//绑定
	struct sockaddr_in tsockaddr_in;
	tsockaddr_in.sin_family = AF_INET;
	tsockaddr_in.sin_port = htons(_ListenPort);
	tsockaddr_in.sin_addr.s_addr = INADDR_ANY;

	nRet = bind(nFd, (const struct sockaddr*)&tsockaddr_in, sizeof tsockaddr_in);
	if (nRet == -1)
	{
		perror("bind failed.");
		return NULL;
	}

	//监听（Linux内核最多可同时监听128个套接字）
	nRet = listen(nFd, 128);
	if (nRet == -1)
	{
		perror("listen failed.");
		return NULL;
	}

	ptLitener_Info->ListenFd = nFd;
	ptLitener_Info->ListenPort = _ListenPort;
	return ptLitener_Info;
}
