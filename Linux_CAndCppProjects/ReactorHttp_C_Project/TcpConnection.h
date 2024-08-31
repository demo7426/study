//�ļ�������
//      ʵ��һ������ģ�飬����EventLoopģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/26
//�޸ļ�¼��
//      2024/1/26     �½�

#pragma once
#include "EventLoop.h"
#include "Channel.h"
#include "Buffer.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

//����������ѡ���һ�ַ������ݵķ�ʽ�����ݺܿ��ܲ�֧�ֳ����ļ����ͣ���֮δ����ú���õڶ��ַ������ݵķ�ʽ��дһ���ֵ��Զ��建�巢��һ����
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

//����
int TcpConnectionDetroy(void* _Arg);
