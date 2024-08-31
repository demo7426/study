//�ļ�������
//      ʵ��һ������ģ�飬����TcpServerģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/26
//�޸ļ�¼��
//      2024/1/26     �½�

#pragma once
#include "ThreadPool.h"

class CTcpServer
{
public:
	CTcpServer() = delete;

	/// <summary>
	/// ��ʼ��
	/// </summary>
	/// <param name="_ListenPort">�����˿�</param>
	/// <param name="_SubThreadNum">�̳߳����߳�����</param>
	CTcpServer(unsigned short _ListenPort, int _SubThreadNum);
	~CTcpServer();

	/// <summary>
	/// ����TcpServer
	/// </summary>
	/// <param name="pTcpServer_Info"></param>
	/// <returns></returns>
	int Run();

private:
	/// <summary>
	/// ��ʼ��
	/// </summary>
	/// <param name="_ListenPort">�����˿�</param>
	/// <returns></returns>
	int LinsterInit();

	static int AcceptReadCallBack(void* _Arg);
private:
	int m_nSubThreadNum;							//�̳߳��ڲ����̵߳�����
	int m_nListenFd;
	unsigned short m_usListenPort;
	CEventLoop* m_pcMainEventLoop;					//���߳��¼�ѭ��ģ��
	CThreadPool* m_pcThreadPool;					//�̳߳�ģ����Ϣ
};


