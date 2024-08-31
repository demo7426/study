//文件描述：
//      实现一个Poll反应堆
//作者：钱锐
//时间：2024/2/18
//修改记录：
//      2024/2/18     新建

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "Dispatcher.h"
#include "PollDispatcher.h"

CPollDispatcher::CPollDispatcher(CEventLoop* _EventLoop_Info):CDispatcher(_EventLoop_Info)
{
	for (int i = 0; i < this->m_nMaxNum; i++)
	{
		this->m_nMaxClientFdIndex = 0;
		this->m_tPollfds[i].fd = -1;
		this->m_tPollfds[i].events = -1;
	}
	this->m_strName = "Poll";
}

CPollDispatcher::~CPollDispatcher()
{
}

int CPollDispatcher::Add()
{
	int i = 0;
	for (; i < this->m_nMaxNum; i++)
	{
		if (this->m_tPollfds[i].fd != -1)
		{
			this->m_tPollfds[i].fd = this->m_pcChannel->GetFd();

			if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::READEVENT)
				this->m_tPollfds[i].events |= POLLIN;

			if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::WRITEEVENT)
				this->m_tPollfds[i].events |= POLLOUT;

			this->m_nMaxClientFdIndex = this->m_nMaxClientFdIndex > i ? this->m_nMaxClientFdIndex : i;

			break;
		}
	}

	if (i >= this->m_nMaxNum)
		return -1;

	return 0;
}

int CPollDispatcher::Delete()
{
	int i = 0;
	for (; i < this->m_nMaxNum; i++)
	{
		if (this->m_tPollfds[i].fd == this->m_pcChannel->GetFd())
		{
			this->m_tPollfds[i].fd = -1;
			this->m_tPollfds[i].events = -1;
			this->m_tPollfds[i].revents = -1;
		}
	}

	if (i >= this->m_nMaxNum)
		return -1;

	this->m_pcChannel->m_pDestroyCallBack(const_cast<void*>(this->m_pcChannel->GetArg()));

	return 0;
}

int CPollDispatcher::Modify()
{
	int i = 0;
	for (; i < this->m_nMaxNum; i++)
	{
		if (this->m_tPollfds[i].fd == this->m_pcChannel->GetFd())
		{
			if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::READEVENT)
				this->m_tPollfds[i].events |= POLLIN;

			if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::WRITEEVENT)
				this->m_tPollfds[i].events |= POLLOUT;

			this->m_nMaxClientFdIndex = this->m_nMaxClientFdIndex > i ? this->m_nMaxClientFdIndex : i;

			break;
		}
	}

	if (i >= this->m_nMaxNum)
		return -1;

	return 0;
}

int CPollDispatcher::Dispatch(int _TimeOut)
{
	if (poll(this->m_tPollfds, this->m_nMaxClientFdIndex + 1, _TimeOut) == -1)
	{
		perror("poll failed.");
		return -1;
	}

	for (int i = 0; i < this->m_nMaxClientFdIndex; i++)
	{
		if (this->m_tPollfds[i].fd == -1)
			continue;

		if (this->m_tPollfds[i].revents & POLLIN)
		{
			//读事件
			m_pcEventLoop_Info->Activate(this->m_tPollfds[i].fd, ENUM_FDEVENT::READEVENT);
		}

		if (this->m_tPollfds[i].revents & POLLOUT)
		{
			//写事件
			m_pcEventLoop_Info->Activate(this->m_tPollfds[i].fd, ENUM_FDEVENT::WRITEEVENT);
		}
	}

	return 0;
}

