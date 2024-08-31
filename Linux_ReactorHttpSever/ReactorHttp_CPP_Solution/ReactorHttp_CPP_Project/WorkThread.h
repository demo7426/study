//�ļ�������
//      ʵ��һ���������߳�ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/20
//�޸ļ�¼��
//      2024/2/20     �½�
#pragma once 
#include <mutex>
#include <condition_variable>
#include <thread>
#include "EventLoop.h"

class CWorkThread
{
public:
	CWorkThread() = delete;
	CWorkThread(int _Index);
	~CWorkThread();

	//����
	void Run();

	inline CEventLoop* GetEventLoop() const
	{
		return m_pcEventLoop;
	}
private:
	void SubThreadRunning();

private:
	CEventLoop* m_pcEventLoop;

	std::thread* m_pcThread;
	std::thread::id m_thThreadId;				//�߳�id
	std::string m_strThreadName;				//�߳�����
	std::mutex m_mMutex;
	std::condition_variable m_Cond;
};

