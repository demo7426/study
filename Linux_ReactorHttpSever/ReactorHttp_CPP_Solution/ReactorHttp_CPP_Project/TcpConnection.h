//文件描述：
//      实现一个连接模块，属于EventLoop模块
//作者：钱锐
//时间：2024/2/22
//修改记录：
//      2024/2/22     新建

#pragma once
#include "EventLoop.h"
#include "Channel.h"
#include "Buffer.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

//若定义了则选择第一种发送数据的方式，数据很可能不支持超大文件发送，反之未定义该宏采用第二种发送数据的方式，写一部分到自定义缓冲发送一部分
#define MSG_SEND_AUTO

class CTcpConnection
{
public:
	CTcpConnection() = delete;
	CTcpConnection(int _ClientFd, CEventLoop* _pEventLoop_Info);
	~CTcpConnection();
private:
	//处理与客户端之间的读取缓冲区事件
	static int ClientProcessRead(void* _Arg);

	//将写缓冲区的数据发送到客户端
	static int ClientProcessSend(void* _Arg);

	static int TcpConnectionDetroy(void* _Arg);
private:
	string m_strName;
	CEventLoop* m_pcEventLoop;
	CChannel* m_pcChannel;
	CBuffer* m_pcReadBuffer;
	CBuffer* m_pcWriteBuffer;

	CHttpRequest* m_pcHttpRequest;
	CHttpResponse* m_pcHttpResponse;
};
