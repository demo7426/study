//�ļ�������
//      ʵ��һ������ģ�飬����TcpServerģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/26
//�޸ļ�¼��
//      2024/1/26     �½�

#pragma once
#include "ThreadPool.h"

typedef struct _LiSTENER_INFO
{
	int ListenFd;
	unsigned short ListenPort;
}LiSTENER_INFO, *PLiSTENER_INFO;

typedef struct _TCPSERVER_INFO
{
	int SubThreadNum;							//�̳߳��ڲ����̵߳�����
	PLiSTENER_INFO pListener_Info;				//listen�����Ϣ
	EVENTLOOP_INFO* pMainEventLoop_Info;		//���߳��¼�ѭ��ģ��
	THREADPOOL_INFO* pThreadPool_Info;			//�̳߳�ģ����Ϣ
}TCPSERVER_INFO, * PTCPSERVER_INFO;

/// <summary>
/// ��ʼ��
/// </summary>
/// <param name="_ListenPort">�����˿�</param>
/// <param name="_SubThreadNum">�̳߳����߳�����</param>
/// <returns></returns>
PTCPSERVER_INFO TcpServerInit(unsigned short _ListenPort, int _SubThreadNum);

/// <summary>
/// ����TcpServer
/// </summary>
/// <param name="pTcpServer_Info"></param>
/// <returns></returns>
int TcpServerRun(PTCPSERVER_INFO pTcpServer_Info);


/////////////////////////////////////////�ڲ��ӿ�/////////////////////////////////////////

/// <summary>
/// ��ʼ��
/// </summary>
/// <param name="_ListenPort">�����˿�</param>
/// <returns></returns>
PLiSTENER_INFO LinsterInit(unsigned short _ListenPort);


