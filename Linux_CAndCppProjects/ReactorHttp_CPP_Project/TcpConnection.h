//�ļ�������
//      ʵ��һ������ģ�飬����EventLoopģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/22
//�޸ļ�¼��
//      2024/2/22     �½�

#pragma once
#include "EventLoop.h"
#include "Channel.h"
#include "Buffer.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

//����������ѡ���һ�ַ������ݵķ�ʽ�����ݺܿ��ܲ�֧�ֳ����ļ����ͣ���֮δ����ú���õڶ��ַ������ݵķ�ʽ��дһ���ֵ��Զ��建�巢��һ����
#define MSG_SEND_AUTO

class CTcpConnection
{
public:
	CTcpConnection() = delete;
	CTcpConnection(int _ClientFd, CEventLoop* _pEventLoop_Info);
	~CTcpConnection();
private:
	//������ͻ���֮��Ķ�ȡ�������¼�
	static int ClientProcessRead(void* _Arg);

	//��д�����������ݷ��͵��ͻ���
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
