#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "TcpServer.h"
#include "TcpConnection.h"

int CTcpServer::AcceptReadCallBack(void* _Arg)
{
	CTcpServer* ptTcpServer_Info = static_cast<CTcpServer*>(_Arg);

	int nFd = accept(ptTcpServer_Info->m_nListenFd, NULL, NULL);
	if (nFd <= 0)
		return -1;

	//将已经建立好连接的客户端文件描述符，递交给子线程处理（主线程只负责连接客户端）
	CEventLoop* ptEventLoop_Info = ptTcpServer_Info->m_pcThreadPool->GetEventLoopObj();
	new CTcpConnection(nFd, ptEventLoop_Info);	//此处一定必须使用new操作符创建出对象，因为后续回调会使用该对象
	return 0;
}

CTcpServer::CTcpServer(unsigned short _ListenPort, int _SubThreadNum)
{
	//必须在LinsterInit函数调用之前进行赋值操作，因为该函数内部会使用这些数据
	this->m_usListenPort = _ListenPort;
	this->m_nSubThreadNum = _SubThreadNum;

	this->LinsterInit();
	this->m_pcMainEventLoop = new CEventLoop();
	this->m_pcThreadPool = new CThreadPool(this->m_pcMainEventLoop, _SubThreadNum);
	this->m_nSubThreadNum = _SubThreadNum;
}

CTcpServer::~CTcpServer()
{
	delete this->m_pcMainEventLoop;
	delete this->m_pcThreadPool;
}

int CTcpServer::Run()
{
	//启动线程池
	this->m_pcThreadPool->Run();

	//添加主线程事件模块监听任务
	CChannel* ptChannel_Info = new CChannel(this->m_nListenFd, ENUM_FDEVENT::READEVENT, AcceptReadCallBack, nullptr, nullptr, this);
	this->m_pcMainEventLoop->AddTask(ptChannel_Info, ELEMENTTYPE::ADD);

	//启动主线程事件循环模块
	this->m_pcMainEventLoop->Run();

	return 0;
}

int CTcpServer::LinsterInit()
{
	//创建socket套接字
	this->m_nListenFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->m_nListenFd == -1)
	{
		perror("socket failed.");
		return -1;
	}

	//设置端口复用
	int nOptVal = 1;
	int nRet = setsockopt(this->m_nListenFd, SOL_SOCKET, SO_REUSEADDR, &nOptVal, sizeof nOptVal);
	if (nRet == -1)
	{
		perror("setsockopt failed.");
		return -1;
	}

	//绑定
	struct sockaddr_in tsockaddr_in;
	tsockaddr_in.sin_family = AF_INET;
	tsockaddr_in.sin_port = htons(this->m_usListenPort);
	tsockaddr_in.sin_addr.s_addr = INADDR_ANY;

	nRet = bind(this->m_nListenFd, (const struct sockaddr*)&tsockaddr_in, sizeof tsockaddr_in);
	if (nRet == -1)
	{
		perror("bind failed.");
		return -1;
	}

	//监听（Linux内核最多可同时监听128个套接字）
	nRet = listen(this->m_nListenFd, 128);
	if (nRet == -1)
	{
		perror("listen failed.");
		return -1;
	}

	return 0;
}
