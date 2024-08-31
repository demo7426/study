#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "ThreadPool.h"

CThreadPool::CThreadPool(CEventLoop* _pMainLoop, int _SubThreadNum)
{
	this->m_nSubThreadNum = _SubThreadNum;
	this->m_nSubThreadIndex = 0;
	this->m_bIsStart = false;
	this->m_pcMainEventLoop = _pMainLoop;
	this->m_pvecWorkThread.clear();
}

CThreadPool::~CThreadPool()
{
	for (auto item : this->m_pvecWorkThread)
		delete item;
	this->m_pvecWorkThread.clear();
}

void CThreadPool::Run()
{
	assert(!this->m_bIsStart);
	if (this->m_pcMainEventLoop->GetThreadId() != std::this_thread::get_id())		//保证必须是主线程调用该函数
	{
		exit(0);
	}

	this->m_bIsStart = true;
	for (int i = 0; i < this->m_nSubThreadNum; i++)
	{
		CWorkThread* pcWorkThread = new CWorkThread(i);
		pcWorkThread->Run();

		this->m_pvecWorkThread.push_back(pcWorkThread);
	}
}

CEventLoop* CThreadPool::GetEventLoopObj()
{
	assert(this->m_bIsStart);
	if (this->m_pcMainEventLoop->GetThreadId() != std::this_thread::get_id())		//保证必须是主线程调用该函数
	{
		exit(0);
	}

	CEventLoop* ptEventLoop_Info = this->m_pcMainEventLoop;	//如果没有子线程，则返回主线程的反应堆实例
	if (this->m_nSubThreadNum > 0)
	{
		ptEventLoop_Info = this->m_pvecWorkThread[this->m_nSubThreadIndex]->GetEventLoop();

		this->m_nSubThreadIndex++;
		this->m_nSubThreadIndex %= this->m_nSubThreadNum;
	}

	return ptEventLoop_Info;
}
