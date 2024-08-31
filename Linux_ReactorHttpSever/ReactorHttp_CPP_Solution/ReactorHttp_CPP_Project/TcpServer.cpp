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

	//���Ѿ����������ӵĿͻ����ļ����������ݽ������̴߳������߳�ֻ�������ӿͻ��ˣ�
	CEventLoop* ptEventLoop_Info = ptTcpServer_Info->m_pcThreadPool->GetEventLoopObj();
	new CTcpConnection(nFd, ptEventLoop_Info);	//�˴�һ������ʹ��new������������������Ϊ�����ص���ʹ�øö���
	return 0;
}

CTcpServer::CTcpServer(unsigned short _ListenPort, int _SubThreadNum)
{
	//������LinsterInit��������֮ǰ���и�ֵ��������Ϊ�ú����ڲ���ʹ����Щ����
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
	//�����̳߳�
	this->m_pcThreadPool->Run();

	//������߳��¼�ģ���������
	CChannel* ptChannel_Info = new CChannel(this->m_nListenFd, ENUM_FDEVENT::READEVENT, AcceptReadCallBack, nullptr, nullptr, this);
	this->m_pcMainEventLoop->AddTask(ptChannel_Info, ELEMENTTYPE::ADD);

	//�������߳��¼�ѭ��ģ��
	this->m_pcMainEventLoop->Run();

	return 0;
}

int CTcpServer::LinsterInit()
{
	//����socket�׽���
	this->m_nListenFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->m_nListenFd == -1)
	{
		perror("socket failed.");
		return -1;
	}

	//���ö˿ڸ���
	int nOptVal = 1;
	int nRet = setsockopt(this->m_nListenFd, SOL_SOCKET, SO_REUSEADDR, &nOptVal, sizeof nOptVal);
	if (nRet == -1)
	{
		perror("setsockopt failed.");
		return -1;
	}

	//��
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

	//������Linux�ں�����ͬʱ����128���׽��֣�
	nRet = listen(this->m_nListenFd, 128);
	if (nRet == -1)
	{
		perror("listen failed.");
		return -1;
	}

	return 0;
}
