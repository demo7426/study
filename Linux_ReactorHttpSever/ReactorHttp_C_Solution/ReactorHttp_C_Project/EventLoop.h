//文件描述：
//      实现一个EventLoop模块
//作者：钱锐
//时间：2024/1/16
//修改记录：
//      2024/1/16     新建，创建接口
//      2024/1/22     实现接口

#pragma once
#include <stdbool.h>
#include <pthread.h>

#include "ChanneMap.h"
#include "Dispatcher.h"

enum ELEMENTTYPE
{
	ADD, DELETE, MODIFY
};

typedef struct _CHANNELELEMENT
{
	enum ELEMENTTYPE Type;									//如何处理当前节点中的channel
	PCHANNEL_INFO ChannelInfo;
	struct _CHANNELELEMENT* pNext;
}CHANNELELEMENT, *PCHANNELELEMENT;

struct _DISPATCHR_INFO;
typedef struct _EVENTLOOP_INFO
{
	bool IsQuit;								//当前EventLoop是否退出;true--退出;false--未退出

	struct _DISPATCHR_INFO* pDispatcher_Info;
	void* pDispatcherData;

	//任务队列
	PCHANNELELEMENT pTaskQHead;
	PCHANNELELEMENT pTaskQTail;

	// ChannelMap
	PCHANNELMAP_INFO pChMap_Info;

	//线程相关
	pthread_t ThreadId;							//线程id
	char ThreadNames[33];						//线程名称
	pthread_mutex_t ThreadMutex;				//线程互斥量

	int SocketPair[2];								//存储本地通信的fd，用于唤醒被阻塞的通信模型，通过socketpair函数初始化
}EVENTLOOP_INFO, *PEVENTLOOP_INFO;

//初始化
PEVENTLOOP_INFO EventLoopInit();

//初始化可指定线程名称
PEVENTLOOP_INFO EventLoopInitEx(const char* _ThreadName);

//启动反应堆模型
int EventLoopRun(PEVENTLOOP_INFO _pEventLoop_Info);

//向任务队列内部添加子任务
int EventLoopAddTask(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info, enum ELEMENTTYPE _Type);

//销毁struct _CHANNEL_INFO* 内存
int EventLoopDestroyChannelInfo(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info);

/////////////////////////////////////////内部接口/////////////////////////////////////////

//处理被激活的文件fd
int EventActivate(PEVENTLOOP_INFO _pEventLoop_Info, int _Fd, enum ENUM_FDEVENT _Event);

//处理任务队列内部的任务
int EventLoopProcessTask(PEVENTLOOP_INFO _pEventLoop_Info);

//处理任务队列内部的任务，添加任务
int EventLoopProcessTask_Add(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info);

//处理任务队列内部的任务，删除任务
int EventLoopProcessTask_Delete(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info);

//处理任务队列内部的任务，修改任务
int EventLoopProcessTask_Modify(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info);


/////////////////////////////////////////内部接口/////////////////////////////////////////