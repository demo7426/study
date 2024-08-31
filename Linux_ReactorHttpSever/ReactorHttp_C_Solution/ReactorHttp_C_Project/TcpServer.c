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

	//���Ѿ����������ӵĿͻ����ļ����������ݽ������̴߳������߳�ֻ�������ӿͻ��ˣ�
	PEVENTLOOP_INFO ptEventLoop_Info = GetEventLoopObj(ptTcpServer_Info->pThreadPool_Info);
	TcpConnectionInit(nFd, ptEventLoop_Info);
	return 0;
}

int TcpServerRun(PTCPSERVER_INFO pTcpServer_Info)
{
	//�����̳߳�
	ThreadPoolRun(pTcpServer_Info->pThreadPool_Info);

	//������߳��¼�ģ���������
	PCHANNEL_INFO ptChannel_Info = ChannelInit(pTcpServer_Info->pListener_Info->ListenFd, READEVENT, AcceptReadCallBack, NULL, NULL, pTcpServer_Info);
	EventLoopAddTask(pTcpServer_Info->pMainEventLoop_Info, ptChannel_Info, ADD);

	//�������߳��¼�ѭ��ģ��
	EventLoopRun(pTcpServer_Info->pMainEventLoop_Info);

	return 0;
}

PLiSTENER_INFO LinsterInit(unsigned short _ListenPort)
{
	PLiSTENER_INFO ptLitener_Info = (PLiSTENER_INFO)malloc(sizeof(LiSTENER_INFO));
	if (ptLitener_Info == NULL)
		return NULL;

	//����socket�׽���
	int nFd = socket(AF_INET, SOCK_STREAM, 0);
	if (nFd == -1)
	{
		perror("socket failed.");
		return NULL;
	}

	//���ö˿ڸ���
	int nOptVal = 1;
	int nRet = setsockopt(nFd, SOL_SOCKET, SO_REUSEADDR, &nOptVal, sizeof nOptVal);
	if (nRet == -1)
	{
		perror("setsockopt failed.");
		return NULL;
	}

	//��
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

	//������Linux�ں�����ͬʱ����128���׽��֣�
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
