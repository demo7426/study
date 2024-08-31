#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>          /* See NOTES */
#include <arpa/inet.h>
#include <unistd.h>

#include "EventLoop.h"

static int WriteLocalMsg(PEVENTLOOP_INFO _pEventLoop_Info)
{
	write(_pEventLoop_Info->SocketPair[0], "1", strlen("1"));
	return 0;
}

static int ReadLocalMsg(void* _Arg)
{
	PEVENTLOOP_INFO ptEventLoop_Info = (PEVENTLOOP_INFO)_Arg;
	char chReadBuf[256] = { 0 };

	read(ptEventLoop_Info->SocketPair[1], chReadBuf, sizeof chReadBuf);
	return 0;
}

PEVENTLOOP_INFO EventLoopInit()
{
	return EventLoopInitEx(NULL);
}

PEVENTLOOP_INFO EventLoopInitEx(const char* _ThreadName)
{
	PEVENTLOOP_INFO ptEventLoop = (PEVENTLOOP_INFO)malloc(sizeof(EVENTLOOP_INFO));
	if (ptEventLoop == NULL)
	{
		perror("malloc failed.");
		return NULL;
	}

	ptEventLoop->IsQuit = false;
	ptEventLoop->pChMap_Info = ChannelMapInit(128);
	ptEventLoop->pDispatcher_Info = &g_tEpollDis_Info;
	ptEventLoop->pDispatcherData = ptEventLoop->pDispatcher_Info->Init();
	ptEventLoop->pTaskQHead = NULL;
	ptEventLoop->pTaskQTail = NULL;
	ptEventLoop->ThreadId = pthread_self();

	pthread_mutex_init(&(ptEventLoop->ThreadMutex), NULL);
	memset(ptEventLoop->ThreadNames, 0, sizeof(ptEventLoop->ThreadNames));
	strncpy(ptEventLoop->ThreadNames, _ThreadName == NULL ? "MainThread" : _ThreadName, sizeof(ptEventLoop->ThreadNames) - 1);

	socketpair(AF_UNIX, SOCK_STREAM, 0, ptEventLoop->SocketPair);
	PCHANNEL_INFO ptChInfo = ChannelInit(ptEventLoop->SocketPair[1], READEVENT, ReadLocalMsg, NULL, NULL, ptEventLoop);
	EventLoopAddTask(ptEventLoop, ptChInfo, ADD);

	return ptEventLoop;
}

int EventLoopRun(PEVENTLOOP_INFO _pEventLoop_Info)
{
	assert(_pEventLoop_Info != NULL);

	if (_pEventLoop_Info->ThreadId != pthread_self())
	{
		return -1;
	}

	PDISPATCHR_INFO ptDispatchr_Info = _pEventLoop_Info->pDispatcher_Info;

	while (!_pEventLoop_Info->IsQuit)
	{
		ptDispatchr_Info->Dispatch(_pEventLoop_Info, 2000);      //超时时长设置为2000ms
		EventLoopProcessTask(_pEventLoop_Info);
	}

	return 0;
}

int EventActivate(PEVENTLOOP_INFO _pEventLoop_Info, int _Fd, enum ENUM_FDEVENT _Event)
{
	if (_pEventLoop_Info == NULL || _Fd < 0)
	{
		return -1;
	}

	//取出
	PCHANNEL_INFO ptChanenel_Info = _pEventLoop_Info->pChMap_Info->List[_Fd];
	assert(ptChanenel_Info->Fd == _Fd);

	if (_Event & READEVENT && ptChanenel_Info->ReadCallBack != NULL)
	{
		ptChanenel_Info->ReadCallBack(ptChanenel_Info->Arg);
	}

	if (_Event & WRITEEVENT && ptChanenel_Info->WriteCallBack != NULL)
	{
		ptChanenel_Info->WriteCallBack(ptChanenel_Info->Arg);
	}

	return 0;
}

int EventLoopAddTask(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info, enum ELEMENTTYPE _Type)
{
	//任务队列是受到多个线程的访问
	pthread_mutex_lock(&(_pEventLoop_Info->ThreadMutex));

	//创建新节点
	PCHANNELELEMENT ptChEle = (PCHANNELELEMENT)malloc(sizeof(CHANNELELEMENT));
	if (ptChEle == NULL)
	{
		perror("malloc failed.");
		return -1;
	}
	ptChEle->Type = _Type;
	ptChEle->pNext = NULL;
	ptChEle->ChannelInfo = _pChannel_Info;

	if (_pEventLoop_Info->pTaskQHead == NULL)
	{
		_pEventLoop_Info->pTaskQHead = _pEventLoop_Info->pTaskQTail = ptChEle;
	}
	else
	{
		_pEventLoop_Info->pTaskQTail->pNext = ptChEle;
		_pEventLoop_Info->pTaskQTail = ptChEle;
	}

	pthread_mutex_unlock(&(_pEventLoop_Info->ThreadMutex));

	//处理细节
	/*
	* 细节：
	*   1.对于链表节点的添加：可能是当前线程也可能是主线程
	*       1).修改fd的事件，当前子线程发起，当前子线程处理
	*       2).添加新的fd，添加任务节点的操作由主线程发起
	*   2.不能让主线程处理任务队列，需要有当前子线程处理
	*/
	if (_pEventLoop_Info->ThreadId == pthread_self())
	{
		//当前子线程处理
		EventLoopProcessTask(_pEventLoop_Info);
	}
	else
	{
		//主线程 -- 告诉子线程处理任务队列里面的任务
		//1.子线程在工作  2.子线程被阻塞了：select、poll、epoll
		WriteLocalMsg(_pEventLoop_Info);
	}


	return 0;
}

int EventLoopProcessTask(PEVENTLOOP_INFO _pEventLoop_Info)
{
	pthread_mutex_lock(&_pEventLoop_Info->ThreadMutex);

	PCHANNELELEMENT ptChEle = _pEventLoop_Info->pTaskQHead;

	while (ptChEle != NULL)
	{
		if (ptChEle->Type == ADD)
		{
			//添加
			EventLoopProcessTask_Add(_pEventLoop_Info, ptChEle->ChannelInfo);
		}
		else if (ptChEle->Type == DELETE)
		{
			//删除
			EventLoopProcessTask_Delete(_pEventLoop_Info, ptChEle->ChannelInfo);

			//TODO:暂未释放内存资源
			//EventLoopDestroyChannelInfo(_pEventLoop_Info, ptChEle->ChannelInfo);
		}
		else if (ptChEle->Type == MODIFY)
		{
			//修改
			EventLoopProcessTask_Modify(_pEventLoop_Info, ptChEle->ChannelInfo);
		}

		PCHANNELELEMENT ptChEleTmp = _pEventLoop_Info->pTaskQHead;
		_pEventLoop_Info->pTaskQHead = _pEventLoop_Info->pTaskQHead->pNext;
		ptChEle = _pEventLoop_Info->pTaskQHead;
		free(ptChEleTmp);
	}

	_pEventLoop_Info->pTaskQHead = _pEventLoop_Info->pTaskQTail = NULL;
	pthread_mutex_unlock(&_pEventLoop_Info->ThreadMutex);

	return 0;
}

int EventLoopProcessTask_Add(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info)
{
	PCHANNELMAP_INFO ptChMap_Info = _pEventLoop_Info->pChMap_Info;
	int nFd = _pChannel_Info->Fd;

	if (ptChMap_Info->Capacity < nFd)
	{
		if (ExpandChannelMapCapacity(ptChMap_Info, nFd + 100) == -1)
			return -1;
	}

	//刷新ChannnelMap、监测文件描述符
	if (ptChMap_Info->List[nFd] == NULL)
	{
		ptChMap_Info->List[nFd] = _pChannel_Info;
		_pEventLoop_Info->pDispatcher_Info->Add(_pChannel_Info, _pEventLoop_Info);
	}

	return 0;
}

int EventLoopProcessTask_Delete(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info)
{
	PCHANNELMAP_INFO ptChMap_Info = _pEventLoop_Info->pChMap_Info;
	int nFd = _pChannel_Info->Fd;

	if (ptChMap_Info->Capacity < nFd)
	{
		return -1;
	}

	return _pEventLoop_Info->pDispatcher_Info->Delete(_pChannel_Info, _pEventLoop_Info);
}

int EventLoopProcessTask_Modify(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info)
{
	PCHANNELMAP_INFO ptChMap_Info = _pEventLoop_Info->pChMap_Info;
	int nFd = _pChannel_Info->Fd;

	if (ptChMap_Info->Capacity < nFd || ptChMap_Info->List[nFd] == NULL)
	{
		return -1;
	}

	return _pEventLoop_Info->pDispatcher_Info->Modify(_pChannel_Info, _pEventLoop_Info);
}

int EventLoopDestroyChannelInfo(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info)
{
	//销毁关于 PCHANNEL_INFO 的资源 
	_pEventLoop_Info->pChMap_Info->List[_pChannel_Info->Fd] = NULL;
	close(_pChannel_Info->Fd);
	free(_pChannel_Info);

	return 0;
}
