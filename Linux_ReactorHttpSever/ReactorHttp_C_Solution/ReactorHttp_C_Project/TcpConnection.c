#include <stdlib.h>
#include <stdio.h>
#include "TcpConnection.h"

//������ͻ���֮��Ķ�ȡ�������¼�
static int ClientProcessRead(void* _Arg)
{
	PTCPCONNECTION_INFO ptTcpCon_Info = (PTCPCONNECTION_INFO)_Arg;
	int nRecvLength = BufferSocketRead(ptTcpCon_Info->pReadBuffer, ptTcpCon_Info->pChannel_Info->Fd);
	if (nRecvLength > 0)
	{
#ifndef MSG_SEND_AUTO
		//���д�¼����
		EnableWriteEvent(ptTcpCon_Info->pChannel_Info, true);
		EventLoopAddTask(ptTcpCon_Info->pEventLoop_Info, ptTcpCon_Info->pChannel_Info, MODIFY);
#endif // !MSG_SEND_AUTO

		//����recv�����ݣ����ܵ�����Ϊhttp���󣬽���
		int nRtn = HttpRequestParase(ptTcpCon_Info->pHttpRequest_Info, ptTcpCon_Info->pReadBuffer, ptTcpCon_Info->pHttpResponse_Info,
			ptTcpCon_Info->pWriteBuffer, ptTcpCon_Info->pChannel_Info->Fd);
		
		if (nRtn != 0)
		{
			BufferAppendString(ptTcpCon_Info->pWriteBuffer, "http/1.1 400 �����ض���\r\n\r\n\r\n");
		}
	}
//	else
//	{
//#ifdef MSG_SEND_AUTO
//		//�ͻ��˶Ͽ����ӣ���ͬ�ڽ��ͻ����ļ��������Ӽ������ڲ��Ƴ���
//		EventLoopAddTask(ptTcpCon_Info->pEventLoop_Info, ptTcpCon_Info->pChannel_Info, DELETE);
//#endif // !MSG_SEND_AUTO
//	}

	//TODO:Ϊʲô��ͻ���֮�䶼Ҫ�Ͽ����ӣ�
	//�ͻ��˶Ͽ����ӣ���ͬ�ڽ��ͻ����ļ��������Ӽ������ڲ��Ƴ���
	EventLoopAddTask(ptTcpCon_Info->pEventLoop_Info, ptTcpCon_Info->pChannel_Info, DELETE);

	
	return 0;
}

//��д�����������ݷ��͵��ͻ���
static int ClientProcessSend(void* _Arg)
{
	PTCPCONNECTION_INFO ptTcpCon_Info = (PTCPCONNECTION_INFO)_Arg;
	int nSendCount = BufferSocketSend(ptTcpCon_Info->pWriteBuffer, ptTcpCon_Info->pChannel_Info->Fd);

	if (nSendCount > 0)
	{
		//�ж������Ƿ���ȫ������ϣ���������Ͽ���ͻ��˵�����
		if (GetBufferContinuousReadSize(ptTcpCon_Info->pWriteBuffer) == 0)
		{
			//�Ͽ��Ϳͻ��˵�����
			EnableWriteEvent(ptTcpCon_Info->pChannel_Info, false);
			EventLoopAddTask(ptTcpCon_Info->pEventLoop_Info, ptTcpCon_Info->pChannel_Info, MODIFY);

			//ǰ���޸ļ���¼��ĺ�������ֱ�Ӳ��õ��ã���Ϊ�ڴ˴�ֱ�ӽ��������ɾ����
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
				

	//���Ѿ����������ӵĿͻ����ļ����������ݽ������̴߳������߳�ֻ�������ӿͻ��ˣ�
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
