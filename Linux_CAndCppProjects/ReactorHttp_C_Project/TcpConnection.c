#include <stdlib.h>
#include <stdio.h>
#include "TcpConnection.h"

//处理与客户端之间的读取缓冲区事件
static int ClientProcessRead(void* _Arg)
{
	PTCPCONNECTION_INFO ptTcpCon_Info = (PTCPCONNECTION_INFO)_Arg;
	int nRecvLength = BufferSocketRead(ptTcpCon_Info->pReadBuffer, ptTcpCon_Info->pChannel_Info->Fd);
	if (nRecvLength > 0)
	{
#ifndef MSG_SEND_AUTO
		//添加写事件检测
		EnableWriteEvent(ptTcpCon_Info->pChannel_Info, true);
		EventLoopAddTask(ptTcpCon_Info->pEventLoop_Info, ptTcpCon_Info->pChannel_Info, MODIFY);
#endif // !MSG_SEND_AUTO

		//处理recv的数据，接受的数据为http请求，解析
		int nRtn = HttpRequestParase(ptTcpCon_Info->pHttpRequest_Info, ptTcpCon_Info->pReadBuffer, ptTcpCon_Info->pHttpResponse_Info,
			ptTcpCon_Info->pWriteBuffer, ptTcpCon_Info->pChannel_Info->Fd);
		
		if (nRtn != 0)
		{
			BufferAppendString(ptTcpCon_Info->pWriteBuffer, "http/1.1 400 永久重定向\r\n\r\n\r\n");
		}
	}
//	else
//	{
//#ifdef MSG_SEND_AUTO
//		//客户端断开连接（等同于将客户端文件描述符从检测队列内部移除）
//		EventLoopAddTask(ptTcpCon_Info->pEventLoop_Info, ptTcpCon_Info->pChannel_Info, DELETE);
//#endif // !MSG_SEND_AUTO
//	}

	//TODO:为什么与客户端之间都要断开连接？
	//客户端断开连接（等同于将客户端文件描述符从检测队列内部移除）
	EventLoopAddTask(ptTcpCon_Info->pEventLoop_Info, ptTcpCon_Info->pChannel_Info, DELETE);

	
	return 0;
}

//将写缓冲区的数据发送到客户端
static int ClientProcessSend(void* _Arg)
{
	PTCPCONNECTION_INFO ptTcpCon_Info = (PTCPCONNECTION_INFO)_Arg;
	int nSendCount = BufferSocketSend(ptTcpCon_Info->pWriteBuffer, ptTcpCon_Info->pChannel_Info->Fd);

	if (nSendCount > 0)
	{
		//判定数据是否完全发送完毕，若满足则断开与客户端的连接
		if (GetBufferContinuousReadSize(ptTcpCon_Info->pWriteBuffer) == 0)
		{
			//断开和客户端的连接
			EnableWriteEvent(ptTcpCon_Info->pChannel_Info, false);
			EventLoopAddTask(ptTcpCon_Info->pEventLoop_Info, ptTcpCon_Info->pChannel_Info, MODIFY);

			//前面修改检测事件的函数可以直接不用调用，因为在此处直接将检测任务删除了
			EventLoopAddTask(ptTcpCon_Info->pEventLoop_Info, ptTcpCon_Info->pChannel_Info, DELETE);
		}

	}
	
	return 0;
}

PTCPCONNECTION_INFO TcpConnectionInit(int _ClientFd, PEVENTLOOP_INFO _pEventLoop_Info)
{
	PTCPCONNECTION_INFO ptTcpCon_Info = (PTCPCONNECTION_INFO)malloc(sizeof(TCPCONNECTION_INFO));
	if (ptTcpCon_Info == NULL)
		return NULL;

	sprintf(ptTcpCon_Info->Name, "TcpConnection-%d", _ClientFd);
	ptTcpCon_Info->pEventLoop_Info = _pEventLoop_Info;
	ptTcpCon_Info->pReadBuffer = BufferInit(10240);
	ptTcpCon_Info->pWriteBuffer = BufferInit(10240);
	ptTcpCon_Info->pHttpRequest_Info = HttpRequestInit();
	ptTcpCon_Info->pHttpResponse_Info = HttpResponseInit();
	ptTcpCon_Info->pChannel_Info = ChannelInit(_ClientFd, READEVENT, ClientProcessRead, ClientProcessSend, TcpConnectionDetroy, ptTcpCon_Info);
				

	//将已经建立好连接的客户端文件描述符，递交给子线程处理（主线程只负责连接客户端）
	EventLoopAddTask(_pEventLoop_Info, ptTcpCon_Info->pChannel_Info, ADD);

	return ptTcpCon_Info;
}

int TcpConnectionDetroy(void* _Arg)
{
	if (_Arg == NULL)
		return -1;

	PTCPCONNECTION_INFO ptTcpCon_Info = (PTCPCONNECTION_INFO)_Arg;

	if (ptTcpCon_Info->pChannel_Info != NULL && GetBufferContinuousReadSize(ptTcpCon_Info->pReadBuffer) ==0 &&
		GetBufferContinuousReadSize(ptTcpCon_Info->pWriteBuffer) == 0 && ptTcpCon_Info->pHttpRequest_Info != NULL &&
		ptTcpCon_Info->pHttpResponse_Info != NULL)
	{
		//free(ptTcpCon_Info->pChannel_Info);
		EventLoopDestroyChannelInfo(ptTcpCon_Info->pEventLoop_Info, ptTcpCon_Info->pChannel_Info);
		free(ptTcpCon_Info->pReadBuffer);
		free(ptTcpCon_Info->pWriteBuffer);
		free(ptTcpCon_Info->pHttpRequest_Info);
		free(ptTcpCon_Info->pHttpResponse_Info);
		free(ptTcpCon_Info);
	}

	return 0;
}
