//Channel模块

#pragma once
#include <stdbool.h>

typedef int(*HandleFunc)(void*);

enum ENUM_FDEVENT
{
	TIMEOUT = 0x01,
	READEVENT = 0x02,
	WRITEEVENT = 0x04
};

typedef struct _CHANNEL_INFO
{
	int Fd;								//文件描述符
	enum ENUM_FDEVENT Events;			//事件

	HandleFunc ReadCallBack;			//读回调函数
	HandleFunc WriteCallBack;			//写回调函数
	HandleFunc DestroyCallBack;			//销毁回调函数

	void* Arg;							//回调函数参数
}CHANNEL_INFO, *PCHANNEL_INFO;


//Channnel初始化函数
PCHANNEL_INFO ChannelInit(int _Fd, enum ENUM_FDEVENT _Events, HandleFunc _ReadCallBack, HandleFunc _WriteCallBack, HandleFunc _DestroyCallBack, void* _Arg);

/// <summary>
/// 使能写事件
/// </summary>
/// <param name="_ChannelInfo"></param>
/// <param name="_Status">true--使能; false--取消使能</param>
void EnableWriteEvent(PCHANNEL_INFO _ChannelInfo, bool _Status);

/// <summary>
/// 检测当前文件描述符的写状态
/// </summary>
/// <param name="_ChannelInfo"></param>
/// <returns>true--已使能; false--未使能</returns>
bool IsEnableWriteEvent(PCHANNEL_INFO _ChannelInfo);
