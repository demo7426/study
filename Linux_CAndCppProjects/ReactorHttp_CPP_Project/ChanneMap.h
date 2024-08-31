#pragma once
#include "Channel.h"

typedef struct _CHANNELMAP_INFO
{
	int Capacity;				//容量大小
	PCHANNEL_INFO* List;		//Map指针数组的起始地址
}CHANNELMAP_INFO, *PCHANNELMAP_INFO;

/// <summary>
/// 创建及初始化 PCHANNELMAP_INFO 对象
/// </summary>
/// <param name="_Capacity">容量</param>
/// <returns>NULL--失败；!NULL--成功</returns>
PCHANNELMAP_INFO ChannelMapInit(int _Capacity);

/// <summary>
/// 销毁指定 PCHANNELMAP_INFO 对象
/// </summary>
/// <param name="_ChannelMap_Info"></param>
/// <returns>-1--失败；0--成功</returns>
int ChannelMapDestroy(PCHANNELMAP_INFO _ChannelMap_Info);

/// <summary>
/// 扩大容量
/// </summary>
/// <param name="_ChannelMap_Info"></param>
/// <param name="_NewCap">传入的容量大小（必须大于当前容量）</param>
/// <returns>-1--失败；0--成功</returns>
int ExpandChannelMapCapacity(PCHANNELMAP_INFO _ChannelMap_Info, int _NewCap);
