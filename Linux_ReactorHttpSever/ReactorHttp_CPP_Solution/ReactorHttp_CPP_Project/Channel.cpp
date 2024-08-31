
#include "Channel.h"

CChannel::CChannel(int _Fd, enum ENUM_FDEVENT _Events, HandleFunc _ReadCallBack, HandleFunc _WriteCallBack, HandleFunc _DestroyCallBack, void* _Arg)
{
	this->m_nFd = _Fd;
	this->m_eEvents = _Events;
	this->m_pReadCallBack = _ReadCallBack;
	this->m_pWriteCallBack = _WriteCallBack;
	this->m_pDestroyCallBack = _DestroyCallBack;
	this->m_pvArg = _Arg;
}

void CChannel::EnableWriteEvent(bool _Status)
{
	if (_Status)
	{
		this->m_eEvents = static_cast<enum ENUM_FDEVENT>(
			(static_cast<int>(this->m_eEvents) | static_cast<int>(ENUM_FDEVENT::WRITEEVENT))
			);
	}
	else
	{
		this->m_eEvents = static_cast<enum ENUM_FDEVENT>(
			(static_cast<int>(this->m_eEvents) & ~static_cast<int>(ENUM_FDEVENT::WRITEEVENT))
			);
	}
}

bool CChannel::IsEnableWriteEvent()
{
	return static_cast<int>(this->m_eEvents) & static_cast<int>(ENUM_FDEVENT::WRITEEVENT);
}
