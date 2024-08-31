//调度程序模块 其中包括select、pool、epoll三种模型
#pragma once
#include "Channel.h"
#include "EventLoop.h"

struct EVENTLOOP_INFO;
typedef struct _DISPATCHR_INFO
{
	//初始化
	void* (*Init)();
	//添加
	int (*Add)(PCHANNEL_INFO _Channel_Info, struct EVENTLOOP_INFO* _EventLoop_Info);
	//删除
	int (*Delete)(PCHANNEL_INFO _Channel_Info, struct EVENTLOOP_INFO* _EventLoop_Info);
	//修改
	int (*Modify)(PCHANNEL_INFO _Channel_Info, struct EVENTLOOP_INFO* _EventLoop_Info);
	//事件监测 _TimeOut：单位为毫秒
	int (*Dispatch)(struct EVENTLOOP_INFO* _EventLoop_Info, int _TimeOut);
	//清除数据(关闭fd、释放内存)
	int (*Clear)(struct EVENTLOOP_INFO* _EventLoop_Info);
}DISPATCHR_INFO, *PDISPATCHR_INFO;

extern struct _DISPATCHR_INFO g_tEpollDis_Info;
extern struct _DISPATCHR_INFO g_tPollDis_Info;
extern struct _DISPATCHR_INFO g_tSelectDis_Info;