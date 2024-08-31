//文件描述：
//      实现一个工作者线程模块
//作者：钱锐
//时间：2024/2/20
//修改记录：
//      2024/2/20     新建
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

	//运行
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
	std::thread::id m_thThreadId;				//线程id
	std::string m_strThreadName;				//线程名称
	std::mutex m_mMutex;
	std::condition_variable m_Cond;
};

