//文件描述：
//      实现一个Poll反应堆
//作者：钱锐
//时间：2024/1/19
//修改记录：
//      2024/1/19     新建
#include <stdlib.h>
#include <stdio.h>
#include <poll.h>
#include <unistd.h>

#include "Dispatcher.h"

#define MAX_POLL_NUM 1024		//poll检测时，最大客户端连接数量

typedef	struct _POLLDATA
{
	int MaxClientFdIndex;			//最大有效客户端文件描述符所在索引位置
	struct pollfd Pollfds[MAX_POLL_NUM];
}POLLDATA, * PPOLLDATA;

//poll初始化
static void* PollInit();
//poll添加
static int PollAdd(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//poll删除
static int PollDelete(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//poll修改
static int PollModify(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//poll事件监测
static int PollDispatch(PEVENTLOOP_INFO _EventLoop_Info, int _TimeOut);
//poll清除数据(关闭fd、释放内存)
static int PollClear(PEVENTLOOP_INFO _EventLoop_Info);

struct _DISPATCHR_INFO g_tPollDis_Info = {
	PollInit, PollAdd, PollDelete, PollModify, PollDispatch, PollClear
};

static void* PollInit()
{
	PPOLLDATA pPollData = (PPOLLDATA)malloc(sizeof(POLLDATA));
	if (pPollData == NULL)
	{
		perror("PollInit malloc failed");
		return NULL;
	}

	for (int i = 0; i < MAX_POLL_NUM; i++)
	{
		pPollData->MaxClientFdIndex = 0;
		pPollData->Pollfds[i].fd = -1;
		pPollData->Pollfds[i].events = -1;
	}

	return pPollData;
}

static int PollAdd(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info)
{
	PPOLLDATA ptPollData = (PPOLLDATA)_EventLoop_Info->pDispatcherData;

	int i = 0;
	for (; i < MAX_POLL_NUM; i++)
	{
		if (ptPollData->Pollfds[i].fd != -1)
		{
			ptPollData->Pollfds[i].fd = _Channel_Info->Fd;

			if (_Channel_Info->Events & READEVENT)
				ptPollData->Pollfds[i].events |= POLLIN;

			if (_Channel_Info->Events & WRITEEVENT)
				ptPollData->Pollfds[i].events |= POLLOUT;

			ptPollData->MaxClientFdIndex = ptPollData->MaxClientFdIndex > i ? ptPollData->MaxClientFdIndex : i;

			break;
		}
	}

	if (i >= MAX_POLL_NUM)
		return -1;

	return 0;
}

static int PollDelete(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info)
{
	PPOLLDATA ptPollData = (PPOLLDATA)_EventLoop_Info->pDispatcherData;

	int i = 0;
	for (; i < MAX_POLL_NUM; i++)
	{
		if (ptPollData->Pollfds[i].fd == _Channel_Info->Fd)
		{
			ptPollData->Pollfds[i].fd = -1;
			ptPollData->Pollfds[i].events = -1;
			ptPollData->Pollfds[i].revents = -1;
		}
	}

	if (i >= MAX_POLL_NUM)
		return -1;

	_Channel_Info->DestroyCallBack(_Channel_Info->Arg);

	return 0;
}

static int PollModify(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info)
{
	PPOLLDATA ptPollData = (PPOLLDATA)_EventLoop_Info->pDispatcherData;

	int i = 0;
	for (; i < MAX_POLL_NUM; i++)
	{
		if (ptPollData->Pollfds[i].fd == _Channel_Info->Fd)
		{
			if (_Channel_Info->Events & READEVENT)
				ptPollData->Pollfds[i].events |= POLLIN;

			if (_Channel_Info->Events & WRITEEVENT)
				ptPollData->Pollfds[i].events |= POLLOUT;

			ptPollData->MaxClientFdIndex = ptPollData->MaxClientFdIndex > i ? ptPollData->MaxClientFdIndex : i;

			break;
		}
	}

	if (i >= MAX_POLL_NUM)
		return -1;

	return 0;
}

static int PollDispatch(PEVENTLOOP_INFO _EventLoop_Info, int _TimeOut)
{
	PPOLLDATA ptPollData = (PPOLLDATA)_EventLoop_Info->pDispatcherData;

	if (poll(ptPollData->Pollfds, ptPollData->MaxClientFdIndex + 1, _TimeOut) == -1)
	{
		perror("poll failed.");
		return -1;
	}

	for (int i = 0; i < ptPollData->MaxClientFdIndex; i++)
	{
		if (ptPollData->Pollfds[i].fd == -1)
			continue;

		if (ptPollData->Pollfds[i].revents & POLLIN)
		{
			//读事件
			EventActivate(_EventLoop_Info, ptPollData->Pollfds[i].fd, READEVENT);
		}

		if (ptPollData->Pollfds[i].revents & POLLOUT)
		{
			//写事件
			EventActivate(_EventLoop_Info, ptPollData->Pollfds[i].fd, WRITEEVENT);
		}
	}

	return 0;
}

static int PollClear(PEVENTLOOP_INFO _EventLoop_Info)
{
	PPOLLDATA ptPollData = (PPOLLDATA)_EventLoop_Info->pDispatcherData;

	free(ptPollData);
	_EventLoop_Info->pDispatcherData = NULL;
}
