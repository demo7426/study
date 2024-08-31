#include <stdlib.h>
#include <stdio.h>
#include "Channel.h"

PCHANNEL_INFO ChannelInit(int _Fd, enum ENUM_FDEVENT _Events, HandleFunc _ReadCallBack, HandleFunc _WriteCallBack, HandleFunc _DestroyCallBack, void* _Arg)
{
	PCHANNEL_INFO ptChannel_Info = (PCHANNEL_INFO)malloc(sizeof(CHANNEL_INFO));
	if (ptChannel_Info == NULL)
	{
		perror("malloc failed.");
		return NULL;
	}

	ptChannel_Info->Fd = _Fd;
	ptChannel_Info->Events = _Events;
	ptChannel_Info->ReadCallBack = _ReadCallBack;
	ptChannel_Info->WriteCallBack = _WriteCallBack;
	ptChannel_Info->DestroyCallBack = _DestroyCallBack;
	ptChannel_Info->Arg = _Arg;

	return ptChannel_Info;
}

void EnableWriteEvent(PCHANNEL_INFO _ChannelInfo, bool _Status)
{
	if (_Status)
	{
		_ChannelInfo->Events |= WRITEEVENT;
	}
	else
	{
		_ChannelInfo->Events &= ~WRITEEVENT;
	}
}

bool IsEnableWriteEvent(PCHANNEL_INFO _ChannelInfo)
{
	return _ChannelInfo->Events & WRITEEVENT;
}
