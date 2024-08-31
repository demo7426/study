//文件描述：
//      实现一个EpollDispatcher模块
//作者：钱锐
//时间：2024/2/18
//修改记录：
//      2024/2/18     新建

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "Dispatcher.h"
#include "EpollDispatcher.h"

CEpollDispatcher::CEpollDispatcher(CEventLoop* _EventLoop_Info):CDispatcher(_EventLoop_Info)
{
	this->m_nEpFd = epoll_create(10);
	if (this->m_nEpFd == -1)
	{
		perror("CEpollDispatcher epoll_create failed");
		exit(0);
	}

	this->m_pcEvents = new struct epoll_event[this->m_nMaxNum];
	if (this->m_pcEvents == nullptr)
	{
		close(this->m_nEpFd);
		perror("EpollInit calloc failed");
		exit(0);
	}
	this->m_strName = "Epoll";
}

CEpollDispatcher::~CEpollDispatcher()
{
	close(this->m_nEpFd);
	delete[] this->m_pcEvents;
	this->m_pcEvents = nullptr;
}

int CEpollDispatcher::Add()
{
	return EpollCtl(EPOLL_CTL_ADD);
}

int CEpollDispatcher::Delete()
{
	int nRtn = EpollCtl(EPOLL_CTL_DEL);

	this->m_pcChannel->m_pDestroyCallBack(const_cast<void*>(this->m_pcChannel->GetArg()));

	return nRtn;
}

int CEpollDispatcher::Modify()
{
	return EpollCtl(EPOLL_CTL_MOD);
}

int CEpollDispatcher::Dispatch(int _TimeOut)
{
	int nNum = epoll_wait(this->m_nEpFd, this->m_pcEvents, this->m_nMaxNum, _TimeOut);

	for (int i = 0; i < nNum; i++)
	{
		int nEvent = this->m_pcEvents[i].events;
		int nFd = this->m_pcEvents[i].data.fd;
		if (nEvent & EPOLLERR || nEvent & EPOLLHUP)
		{
			//客户端断开连接
			Delete();
			//EpollDelete(_EventLoop_Info->pChMap_Info, _EventLoop_Info);
		}

		if (nEvent & EPOLLIN)	//读取数据
		{
			m_pcEventLoop_Info->Activate(nFd, ENUM_FDEVENT::READEVENT);
		}

		if (nEvent & EPOLLOUT)	//写入数据
		{
			m_pcEventLoop_Info->Activate(nFd, ENUM_FDEVENT::WRITEEVENT);
		}
	}

	return 0;
}

int CEpollDispatcher::EpollCtl(int _Op)
{
	struct epoll_event tepoll_event;
	memset(&tepoll_event, 0, sizeof tepoll_event);

	if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::READEVENT)
		tepoll_event.events |= EPOLLIN;
	if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::WRITEEVENT)
		tepoll_event.events |= EPOLLOUT;
	tepoll_event.data.fd = this->m_pcChannel->GetFd();

	return epoll_ctl(this->m_nEpFd, _Op, this->m_pcChannel->GetFd(), &tepoll_event);
}
