//�ļ�������
//      ʵ��һ���������߳�ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/24
//�޸ļ�¼��
//      2024/1/24     �½�
#include <stdio.h>

#include "WorkThread.h"

using namespace std;

void CWorkThread::SubThreadRunning()
{
	this->m_mMutex.lock();
	this->m_pcEventLoop = new CEventLoop(this->m_strThreadName);
	this->m_mMutex.unlock();
	this->m_Cond.notify_one();
	
	this->m_pcEventLoop->Run();
}

CWorkThread::CWorkThread(int _Index)
{
	this->m_thThreadId = thread::id();
	this->m_strThreadName = "Subthread-" + to_string(_Index);
	this->m_pcEventLoop = nullptr;
}

CWorkThread::~CWorkThread()
{
	if (m_pcThread != nullptr)
	{
		delete m_pcThread; 
		m_pcThread = nullptr;
	}
}

void CWorkThread::Run()
{
	m_pcThread = new thread(&CWorkThread::SubThreadRunning, this);

	//��֤���̳߳�ʼ��EventLoop�ɹ�����ֹ���������ָ�뵼�³������
	unique_lock<mutex> uniqueLock(this->m_mMutex);
	while (this->m_pcEventLoop == nullptr)
	{
		this->m_Cond.wait(uniqueLock);
	}
}
