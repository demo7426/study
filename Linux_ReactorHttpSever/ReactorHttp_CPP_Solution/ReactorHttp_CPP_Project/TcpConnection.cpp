#include <stdlib.h>
#include <stdio.h>
#include "TcpConnection.h"

//处理与客户端之间的读取缓冲区事件
int CTcpConnection::ClientProcessRead(void* _Arg)
{
	CTcpConnection* ptTcpCon_Info = (CTcpConnection*)_Arg;
	int nRecvLength = ptTcpCon_Info->m_pcReadBuffer->SocketRead(ptTcpCon_Info->m_pcChannel->GetFd());
	if (nRecvLength > 0)
	{
#ifndef MSG_SEND_AUTO
		//添加写事件检测
		ptTcpCon_Info->pChannel_Info->EnableWriteEvent(true);
		ptTcpCon_Info->pEventLoop_Info->AddTask(ptTcpCon_Info->pChannel_Info, ELEMENTTYPE::MODIFY);
#endif // !MSG_SEND_AUTO

		//处理recv的数据，接受的数据为http请求，解析
		int nRtn = ptTcpCon_Info->m_pcHttpRequest->Parase(ptTcpCon_Info->m_pcReadBuffer, ptTcpCon_Info->m_pcHttpResponse,
			ptTcpCon_Info->m_pcWriteBuffer, ptTcpCon_Info->m_pcChannel->GetFd());
		
		if (nRtn != 0)
		{
			ptTcpCon_Info->m_pcWriteBuffer->AppendString("http/1.1 400 永久重定向\r\n\r\n\r\n");
		}
	}
//	else
//	{
//#ifdef MSG_SEND_AUTO
//		//客户端断开连接（等同于将客户端文件描述符从检测队列内部移除）
//		ptTcpCon_Info->pEventLoop_Info->AddTask(ptTcpCon_Info->pChannel_Info, ELEMENTTYPE::DELETE);
//#endif // !MSG_SEND_AUTO
//	}

	//TODO:为什么与客户端之间都要断开连接？
	//客户端断开连接（等同于将客户端文件描述符从检测队列内部移除）
	ptTcpCon_Info->m_pcEventLoop->AddTask(ptTcpCon_Info->m_pcChannel, ELEMENTTYPE::DELETE);

	return 0;
}

//将写缓冲区的数据发送到客户端
int CTcpConnection::ClientProcessSend(void* _Arg)
{
	CTcpConnection* ptTcpCon_Info = (CTcpConnection*)_Arg;
	int nSendCount = ptTcpCon_Info->m_pcWriteBuffer->SocketSend(ptTcpCon_Info->m_pcChannel->GetFd());

	if (nSendCount > 0)
	{
		//判定数据是否完全发送完毕，若满足则断开与客户端的连接
		if (ptTcpCon_Info->m_pcWriteBuffer->GetBufferContinuousReadSize() == 0)
		{
			//断开和客户端的连接
			ptTcpCon_Info->m_pcChannel->EnableWriteEvent(false);
			ptTcpCon_Info->m_pcEventLoop->AddTask(ptTcpCon_Info->m_pcChannel, ELEMENTTYPE::MODIFY);

			//前面修改检测事件的函数可以直接不用调用，因为在此处直接将检测任务删除了
			ptTcpCon_Info->m_pcEventLoop->AddTask(ptTcpCon_Info->m_pcChannel, ELEMENTTYPE::DELETE);
		}

	}
	
	return 0;
}

int CTcpConnection::TcpConnectionDetroy(void* _Arg)
{
	if (_Arg == nullptr)
		return -1;

	CTcpConnection* ptTcpCon_Info = (CTcpConnection*)_Arg;
	if (ptTcpCon_Info->m_pcChannel != nullptr && ptTcpCon_Info->m_pcReadBuffer->GetBufferContinuousReadSize() == 0 &&
		ptTcpCon_Info->m_pcWriteBuffer->GetBufferContinuousReadSize() == 0 && ptTcpCon_Info->m_pcHttpRequest != nullptr &&
		ptTcpCon_Info->m_pcHttpResponse != nullptr)
	{
		ptTcpCon_Info->m_pcEventLoop->DestroyChannelInfo(ptTcpCon_Info->m_pcChannel);
		delete ptTcpCon_Info->m_pcReadBuffer;
		delete ptTcpCon_Info->m_pcWriteBuffer;
		delete ptTcpCon_Info->m_pcHttpRequest;
		delete ptTcpCon_Info->m_pcHttpResponse;
	}
	return 0;
}

CTcpConnection::CTcpConnection(int _ClientFd, CEventLoop* _pEventLoop_Info)
{
	this->m_strName = "TcpConnection-" + to_string(_ClientFd);
	this->m_pcEventLoop = _pEventLoop_Info;
	this->m_pcReadBuffer = new CBuffer(10240);
	this->m_pcWriteBuffer = new CBuffer(10240);
	this->m_pcHttpRequest = new CHttpRequest();
	this->m_pcHttpResponse = new CHttpResponse();
	this->m_pcChannel = new CChannel(_ClientFd, ENUM_FDEVENT::READEVENT, ClientProcessRead, ClientProcessSend, TcpConnectionDetroy, this);


	//将已经建立好连接的客户端文件描述符，递交给子线程处理（主线程只负责连接客户端）
	_pEventLoop_Info->AddTask(this->m_pcChannel, ELEMENTTYPE::ADD);
}

CTcpConnection::~CTcpConnection()
{
}

