#include <stdlib.h>
#include <stdio.h>
#include "TcpConnection.h"

//������ͻ���֮��Ķ�ȡ�������¼�
int CTcpConnection::ClientProcessRead(void* _Arg)
{
	CTcpConnection* ptTcpCon_Info = (CTcpConnection*)_Arg;
	int nRecvLength = ptTcpCon_Info->m_pcReadBuffer->SocketRead(ptTcpCon_Info->m_pcChannel->GetFd());
	if (nRecvLength > 0)
	{
#ifndef MSG_SEND_AUTO
		//���д�¼����
		ptTcpCon_Info->pChannel_Info->EnableWriteEvent(true);
		ptTcpCon_Info->pEventLoop_Info->AddTask(ptTcpCon_Info->pChannel_Info, ELEMENTTYPE::MODIFY);
#endif // !MSG_SEND_AUTO

		//����recv�����ݣ����ܵ�����Ϊhttp���󣬽���
		int nRtn = ptTcpCon_Info->m_pcHttpRequest->Parase(ptTcpCon_Info->m_pcReadBuffer, ptTcpCon_Info->m_pcHttpResponse,
			ptTcpCon_Info->m_pcWriteBuffer, ptTcpCon_Info->m_pcChannel->GetFd());
		
		if (nRtn != 0)
		{
			ptTcpCon_Info->m_pcWriteBuffer->AppendString("http/1.1 400 �����ض���\r\n\r\n\r\n");
		}
	}
//	else
//	{
//#ifdef MSG_SEND_AUTO
//		//�ͻ��˶Ͽ����ӣ���ͬ�ڽ��ͻ����ļ��������Ӽ������ڲ��Ƴ���
//		ptTcpCon_Info->pEventLoop_Info->AddTask(ptTcpCon_Info->pChannel_Info, ELEMENTTYPE::DELETE);
//#endif // !MSG_SEND_AUTO
//	}

	//TODO:Ϊʲô��ͻ���֮�䶼Ҫ�Ͽ����ӣ�
	//�ͻ��˶Ͽ����ӣ���ͬ�ڽ��ͻ����ļ��������Ӽ������ڲ��Ƴ���
	ptTcpCon_Info->m_pcEventLoop->AddTask(ptTcpCon_Info->m_pcChannel, ELEMENTTYPE::DELETE);

	return 0;
}

//��д�����������ݷ��͵��ͻ���
int CTcpConnection::ClientProcessSend(void* _Arg)
{
	CTcpConnection* ptTcpCon_Info = (CTcpConnection*)_Arg;
	int nSendCount = ptTcpCon_Info->m_pcWriteBuffer->SocketSend(ptTcpCon_Info->m_pcChannel->GetFd());

	if (nSendCount > 0)
	{
		//�ж������Ƿ���ȫ������ϣ���������Ͽ���ͻ��˵�����
		if (ptTcpCon_Info->m_pcWriteBuffer->GetBufferContinuousReadSize() == 0)
		{
			//�Ͽ��Ϳͻ��˵�����
			ptTcpCon_Info->m_pcChannel->EnableWriteEvent(false);
			ptTcpCon_Info->m_pcEventLoop->AddTask(ptTcpCon_Info->m_pcChannel, ELEMENTTYPE::MODIFY);

			//ǰ���޸ļ���¼��ĺ�������ֱ�Ӳ��õ��ã���Ϊ�ڴ˴�ֱ�ӽ��������ɾ����
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


	//���Ѿ����������ӵĿͻ����ļ����������ݽ������̴߳������߳�ֻ�������ӿͻ��ˣ�
	_pEventLoop_Info->AddTask(this->m_pcChannel, ELEMENTTYPE::ADD);
}

CTcpConnection::~CTcpConnection()
{
}

