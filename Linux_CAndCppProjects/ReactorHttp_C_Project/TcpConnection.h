//文件描述：
//      实现一个连接模块，属于EventLoop模块
//作者：钱锐
//时间：2024/1/26
//修改记录：
//      2024/1/26     新建

#pragma once
#include "EventLoop.h"
#include "Channel.h"
#include "Buffer.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

//若定义了则选择第一种发送数据的方式，数据很可能不支持超大文件发送，反之未定义该宏采用第二种发送数据的方式，写一部分到自定义缓冲发送一部分
#define MSG_SEND_AUTO

typedef struct _TCPCONNECTION_INFO
{
	char Name[32];
	PEVENTLOOP_INFO pEventLoop_Info;
	PCHANNEL_INFO pChannel_Info;
	PBUFFER_INFO pReadBuffer;
	PBUFFER_INFO pWriteBuffer;

	PHTTPREQUEST_INFO pHttpRequest_Info;
	PHTTPRESPONSE_INFO pHttpResponse_Info;
}TCPCONNECTION_INFO, *PTCPCONNECTION_INFO;

PTCPCONNECTION_INFO TcpConnectionInit(int _ClientFd, PEVENTLOOP_INFO _pEventLoop_Info);

//销毁
int TcpConnectionDetroy(void* _Arg);
