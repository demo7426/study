//文件描述：
//      实现一个Select反应堆
//作者：钱锐
//时间：2024/1/21
//修改记录：
//      2024/1/21     新建
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

#include "SelectDispatcher.h"

CSelectDispatcher::CSelectDispatcher(CEventLoop* _EventLoop_Info):CDispatcher(_EventLoop_Info)
{
	this->m_nMaxClientFd = -1;
	FD_ZERO(&this->m_tReadFdSet);
	FD_ZERO(&this->m_tWriteFdSet);
}

CSelectDispatcher::~CSelectDispatcher()
{
}

int CSelectDispatcher::Add() 
{
	this->m_nMaxClientFd = this->m_nMaxClientFd > this->m_pcChannel->GetFd() ? this->m_nMaxClientFd : this->m_pcChannel->GetFd();

	if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::READEVENT)
	{
		FD_SET(this->m_pcChannel->GetFd(), &this->m_tReadFdSet);
	}
	if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::WRITEEVENT)
	{
		FD_SET(this->m_pcChannel->GetFd(), &this->m_tWriteFdSet);
	}

	return 0;
}

int CSelectDispatcher::Delete()
{
	if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::READEVENT)
	{
		FD_CLR(this->m_pcChannel->GetFd(), &this->m_tReadFdSet);
	}
	if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::WRITEEVENT)
	{
		FD_CLR(this->m_pcChannel->GetFd(), &this->m_tWriteFdSet);
	}

	this->m_pcChannel->m_pDestroyCallBack(const_cast<void*>(this->m_pcChannel->GetArg()));

	return 0;
}

int CSelectDispatcher::Modify()
{
	if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::READEVENT)
	{
		FD_CLR(this->m_pcChannel->GetFd(), &this->m_tWriteFdSet);
		FD_SET(this->m_pcChannel->GetFd(), &this->m_tReadFdSet);
	}

	if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::WRITEEVENT)
	{
		FD_CLR(this->m_pcChannel->GetFd(), &this->m_tReadFdSet);
		FD_SET(this->m_pcChannel->GetFd(), &this->m_tWriteFdSet);
	}

	if ((int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::READEVENT && (int)this->m_pcChannel->GetEvents() & (int)ENUM_FDEVENT::WRITEEVENT)
	{
		FD_SET(this->m_pcChannel->GetFd(), &this->m_tReadFdSet);
		FD_SET(this->m_pcChannel->GetFd(), &this->m_tWriteFdSet);
	}
	else
	{
		FD_CLR(this->m_pcChannel->GetFd(), &this->m_tReadFdSet);
		FD_CLR(this->m_pcChannel->GetFd(), &this->m_tWriteFdSet);
	}

	return 0;
}

int CSelectDispatcher::Dispatch(int _TimeOut)
{
	struct timeval ttimeval;
	ttimeval.tv_sec = 0;
	ttimeval.tv_usec = _TimeOut * 1000;

	fd_set ReadSetTmp = this->m_tReadFdSet;
	fd_set WriteSetTmp = this->m_tWriteFdSet;
	int nRtn = select(this->m_nMaxClientFd + 1, &ReadSetTmp, &WriteSetTmp, NULL, &ttimeval);
	if (nRtn == -1)
	{
		perror("select failed");
		return -1;
	}

	for (int i = 0; i <= this->m_nMaxClientFd; i++)
	{
		if (FD_ISSET(i, &ReadSetTmp))
		{
			//读数据
			m_pcEventLoop_Info->Activate(i, ENUM_FDEVENT::READEVENT);
		}

		if (FD_ISSET(i, &WriteSetTmp))
		{
			//写数据
			m_pcEventLoop_Info->Activate(i, ENUM_FDEVENT::WRITEEVENT);
		}

	}

	return 0;
}
