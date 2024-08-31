#include "ChanneMap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PCHANNELMAP_INFO ChannelMapInit(int _Capacity)
{
	PCHANNELMAP_INFO pChannelMap_Info = (PCHANNELMAP_INFO)malloc(sizeof(CHANNELMAP_INFO));
	if (pChannelMap_Info == NULL)
		return NULL;

	pChannelMap_Info->Capacity = _Capacity;
	pChannelMap_Info->List = (PCHANNEL_INFO*)malloc(sizeof(PCHANNEL_INFO) * _Capacity);
	if (pChannelMap_Info->List == NULL)
	{
		free(pChannelMap_Info);
		pChannelMap_Info = NULL;
		return NULL;
	}
	
	memset(pChannelMap_Info->List, 0, sizeof(PCHANNEL_INFO) * _Capacity);

	return pChannelMap_Info;
}

int ChannelMapDestroy(PCHANNELMAP_INFO _ChannelMap_Info)
{
	if (_ChannelMap_Info == NULL)
		return -1;

	for (int i = 0; i < _ChannelMap_Info->Capacity; i++)
	{
		if (_ChannelMap_Info->List[i] == NULL)
			continue;

		free(_ChannelMap_Info->List[i]);
		_ChannelMap_Info->List[i] = NULL;
	}

	free(_ChannelMap_Info);
	_ChannelMap_Info = NULL;

	return 0;
}

int ExpandChannelMapCapacity(PCHANNELMAP_INFO _ChannelMap_Info, int _NewCap)
{
	if (_ChannelMap_Info == NULL || _NewCap <= _ChannelMap_Info->Capacity)
		return -1;

	PCHANNELMAP_INFO pInfo_Tmp = NULL;

	pInfo_Tmp = realloc(_ChannelMap_Info->List, sizeof(PCHANNEL_INFO) * _NewCap);
	if (pInfo_Tmp == NULL)
		return -1;

	////处理是在原来的基础上扩容，还是重新分配了内存
	//if (pInfo_Tmp != _ChannelMap_Info->List)
	//{
	//	memset(pInfo_Tmp, 0, sizeof(PCHANNEL_INFO) * _NewCap);
	//	memcpy(pInfo_Tmp, _ChannelMap_Info->List, sizeof(PCHANNEL_INFO) * _ChannelMap_Info->Capacity);

	//	free(_ChannelMap_Info->List);
	//	_ChannelMap_Info->List = NULL;
	//}
	//else
	//{
	//	memset(_ChannelMap_Info->List + _ChannelMap_Info->Capacity, 0, sizeof(PCHANNEL_INFO) * _NewCap);
	//}
	memset(pInfo_Tmp + _ChannelMap_Info->Capacity, 0, sizeof(PCHANNEL_INFO) * (_NewCap - _ChannelMap_Info->Capacity));
	_ChannelMap_Info->List = pInfo_Tmp;
	_ChannelMap_Info->Capacity = _NewCap;

	return 0;
}
