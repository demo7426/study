//�ļ�������
//      ʵ��һ���̳߳�ģ�飨�̳߳���������1���̣߳���Ϊ�������һ�����̣߳�
//���ߣ�Ǯ��
//ʱ�䣺2024/2/20
//�޸ļ�¼��
//      2024/2/20     �½�
#pragma once
#include <stdbool.h>
#include <vector>

#include "WorkThread.h"

class CThreadPool
{
public:
	CThreadPool() = delete;
	CThreadPool(CEventLoop* _pMainLoop, int _SubThreadNum);
	~CThreadPool();

	// �̳߳�����
	void Run();

	//��ȡ��Ӧ��ʵ��ָ�룬���������¼�ѭ���ڲ�����������������
	CEventLoop* GetEventLoopObj();

private:
	bool m_bIsStart;								//�̳߳��Ƿ�����;true--������,false--δ����
	int m_nSubThreadNum;							//�̳߳��ڲ����߳�����
	int m_nSubThreadIndex;							//���߳�����

	CEventLoop* m_pcMainEventLoop;					//���߳��¼�ѭ��ģ��
	std::vector<CWorkThread*> m_pvecWorkThread;		//���̹߳������߳���ʼ��ַ		
};

