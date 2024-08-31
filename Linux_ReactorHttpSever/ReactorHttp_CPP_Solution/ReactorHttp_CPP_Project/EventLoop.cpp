#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>          /* See NOTES */
#include <arpa/inet.h>
#include <unistd.h>


#include "SelectDispatcher.h"
#include "PollDispatcher.h"
#include "EpollDispatcher.h"
#include "EventLoop.h"

using namespace std;

int CEventLoop::WriteLocalMsg()
{
	write(this->m_nSocketPairs[0], "1", strlen("1"));
	return 0;
}

int CEventLoop::ReadLocalMsg()
{
	char chReadBuf[256] = { 0 };

	read(this->m_nSocketPairs[1], chReadBuf, sizeof chReadBuf);
	return 0;
}

int CEventLoop::ProcessTask()
{
	while (!this->m_queTaskQ.empty())
	{
		this->m_ThreadMutex.lock();
		PCHANNELELEMENT ptChEle = this->m_queTaskQ.front();
		this->m_queTaskQ.pop();

		this->m_ThreadMutex.unlock();

		if (ptChEle->Type == ELEMENTTYPE::ADD)
		{
			//添加
			ProcessTask_Add(ptChEle->ChannelInfo);
		}
		else if (ptChEle->Type == ELEMENTTYPE::DELETE)
		{
			//删除
			ProcessTask_Delete(ptChEle->ChannelInfo);

			//TODO:暂未释放内存资源
			//EventLoopDestroyChannelInfo(_pEventLoop_Info, ptChEle->ChannelInfo);
		}
		else if (ptChEle->Type == ELEMENTTYPE::MODIFY)
		{
			//修改
			ProcessTask_Modify(ptChEle->ChannelInfo);
		}

		delete ptChEle;
	}

	return 0;
}

int CEventLoop::ProcessTask_Add(CChannel* _pChannel_Info)
{
	int nFd = _pChannel_Info->GetFd();

	//刷新ChannnelMap、监测文件描述符
	if (this->pChMap_Info.find(nFd) == this->pChMap_Info.end())
	{
		this->pChMap_Info.insert(make_pair(nFd, _pChannel_Info));

		this->m_pcDispatcher->SetChannel(_pChannel_Info);
		this->m_pcDispatcher->Add();
	}

	return 0;
}

int CEventLoop::ProcessTask_Delete(CChannel* _pChannel_Info)
{
	int nFd = _pChannel_Info->GetFd();
	this->pChMap_Info.erase(nFd);

	this->m_pcDispatcher->SetChannel(_pChannel_Info);
	return this->m_pcDispatcher->Delete();
}

int CEventLoop::ProcessTask_Modify(CChannel* _pChannel_Info)
{
	int nFd = _pChannel_Info->GetFd();

	this->m_pcDispatcher->SetChannel(_pChannel_Info);
	return this->m_pcDispatcher->Modify();
}

int CEventLoop::DestroyChannelInfo(CChannel* _pChannel_Info)
{
	//销毁关于 PCHANNEL_INFO 的资源 
	this->pChMap_Info.erase(_pChannel_Info->GetFd());

	close(_pChannel_Info->GetFd());
	delete _pChannel_Info;

	return 0;
}

CEventLoop::CEventLoop() : CEventLoop(std::string())		//委托构造函数
{
}

CEventLoop::CEventLoop(string _ThreadName)
{
	this->IsQuit = false;
	this->pChMap_Info.clear();
	this->m_pcDispatcher = new CEpollDispatcher(this);
	this->m_thThreadId = std::this_thread::get_id();

	this->m_strThreadNames = _ThreadName == std::string() ? "MainThread" : _ThreadName;

	socketpair(AF_UNIX, SOCK_STREAM, 0, this->m_nSocketPairs);
	
	auto obj = bind(&CEventLoop::ReadLocalMsg, this);
	CChannel* ptChannel = new CChannel(this->m_nSocketPairs[1], ENUM_FDEVENT::READEVENT, obj, nullptr, nullptr, this);
	this->AddTask(ptChannel, ELEMENTTYPE::ADD);
}

int CEventLoop::Run()
{
	if (this->m_thThreadId != this_thread::get_id())
	{
		return -1;
	}

	while (!this->IsQuit)
	{
		this->m_pcDispatcher->Dispatch(2000);		//超时时长设置为2000ms
		ProcessTask();
	}

	return 0;
}

int CEventLoop::AddTask(CChannel* _pChannel_Info, ELEMENTTYPE _Type)
{
	//任务队列是受到多个线程的访问
	this->m_ThreadMutex.lock();

	//创建新节点
	PCHANNELELEMENT ptChEle = new CHANNELELEMENT;
	if (ptChEle == nullptr)
	{
		perror("malloc failed.");
		return -1;
	}
	ptChEle->Type = _Type;
	ptChEle->ChannelInfo = _pChannel_Info;

	this->m_queTaskQ.push(ptChEle);
	this->m_ThreadMutex.unlock();

	//处理细节
	/*
	* 细节：
	*   1.对于链表节点的添加：可能是当前线程也可能是主线程
	*       1).修改fd的事件，当前子线程发起，当前子线程处理
	*       2).添加新的fd，添加任务节点的操作由主线程发起
	*   2.不能让主线程处理任务队列，需要有当前子线程处理
	*/
	if (this->m_thThreadId == this_thread::get_id())
	{
		//当前子线程处理
		ProcessTask();
	}
	else
	{
		//主线程 -- 告诉子线程处理任务队列里面的任务
		//1.子线程在工作  2.子线程被阻塞了：select、poll、epoll
		WriteLocalMsg();
	}


	return 0;
}

int CEventLoop::Activate(int _Fd, ENUM_FDEVENT _Event)
{
	if (_Fd < 0)
	{
		return -1;
	}

	//取出
	CChannel* ptChanenel_Info = this->pChMap_Info[_Fd];
	assert(ptChanenel_Info->GetFd() == _Fd);

	if ((int)_Event & (int)ENUM_FDEVENT::READEVENT && ptChanenel_Info->m_pReadCallBack != nullptr)
	{
		ptChanenel_Info->m_pReadCallBack(const_cast<void*>(ptChanenel_Info->GetArg()));
	}

	if ((int)_Event & (int)ENUM_FDEVENT::WRITEEVENT && ptChanenel_Info->m_pWriteCallBack != nullptr)
	{
		ptChanenel_Info->m_pWriteCallBack(const_cast<void*>(ptChanenel_Info->GetArg()));
	}

	return 0;
}
