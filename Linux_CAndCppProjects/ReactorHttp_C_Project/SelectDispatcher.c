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

#include "Dispatcher.h"

typedef	struct _SELECTDATA
{
	int MaxClientFd;			//最大有效客户端文件描述符
	fd_set ReadFdSet;
	fd_set WriteFdSet;
}SELECTDATA, * PSELECTDATA;

//select初始化
static void* SelectInit();
//select添加
static int SelectAdd(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//select删除
static int SelectDelete(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//select修改
static int SelectModify(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//select事件监测
static int SelectDispatch(PEVENTLOOP_INFO _EventLoop_Info, int _TimeOut);
//select清除数据(关闭fd、释放内存)
static int SelectClear(PEVENTLOOP_INFO _EventLoop_Info);

struct _DISPATCHR_INFO g_tSelectDis_Info = {
	SelectInit, SelectAdd, SelectDelete, SelectModify, SelectDispatch, SelectClear
};

static void* SelectInit()
{
	PSELECTDATA ptSelectData = (PSELECTDATA)malloc(sizeof(SELECTDATA));
	if (ptSelectData == NULL)
	{
		perror("SelectInit malloc failed");
		return NULL;
	}

	ptSelectData->MaxClientFd = -1;
	FD_ZERO(&ptSelectData->ReadFdSet);
	FD_ZERO(&ptSelectData->WriteFdSet);

	return ptSelectData;
}

static int SelectAdd(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info)
{
	PSELECTDATA ptSelectData = (PSELECTDATA)_EventLoop_Info->pDispatcherData;

	ptSelectData->MaxClientFd = ptSelectData->MaxClientFd > _Channel_Info->Fd ? ptSelectData->MaxClientFd : _Channel_Info->Fd;

	if (_Channel_Info->Events & READEVENT)
	{
		FD_SET(_Channel_Info->Fd, &ptSelectData->ReadFdSet);
	}
	if (_Channel_Info->Events & WRITEEVENT)
	{
		FD_SET(_Channel_Info->Fd, &ptSelectData->WriteFdSet);
	}

	return 0;
}

static int SelectDelete(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info)
{
	PSELECTDATA ptSelectData = (PSELECTDATA)_EventLoop_Info->pDispatcherData;

	if (_Channel_Info->Events & READEVENT)
	{
		FD_CLR(_Channel_Info->Fd, &ptSelectData->ReadFdSet);
	}
	if (_Channel_Info->Events & WRITEEVENT)
	{
		FD_CLR(_Channel_Info->Fd, &ptSelectData->WriteFdSet);
	}

	_Channel_Info->DestroyCallBack(_Channel_Info->Arg);

	return 0;
}

static int SelectModify(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info)
{
	PSELECTDATA ptSelectData = (PSELECTDATA)_EventLoop_Info->pDispatcherData;

	if (_Channel_Info->Events & READEVENT)
	{
		FD_CLR(_Channel_Info->Fd, &ptSelectData->WriteFdSet);
		FD_SET(_Channel_Info->Fd, &ptSelectData->ReadFdSet);
	}

	if (_Channel_Info->Events & WRITEEVENT)
	{
		FD_CLR(_Channel_Info->Fd, &ptSelectData->ReadFdSet);
		FD_SET(_Channel_Info->Fd, &ptSelectData->WriteFdSet);
	}

	if (_Channel_Info->Events & READEVENT && _Channel_Info->Events & WRITEEVENT)
	{
		FD_SET(_Channel_Info->Fd, &ptSelectData->ReadFdSet);
		FD_SET(_Channel_Info->Fd, &ptSelectData->WriteFdSet);
	}
	else
	{
		FD_CLR(_Channel_Info->Fd, &ptSelectData->ReadFdSet);
		FD_CLR(_Channel_Info->Fd, &ptSelectData->WriteFdSet);
	}

	return 0;
}

static int SelectDispatch(PEVENTLOOP_INFO _EventLoop_Info, int _TimeOut)
{
	PSELECTDATA ptSelectData = (PSELECTDATA)_EventLoop_Info->pDispatcherData;

	struct timeval ttimeval;
	ttimeval.tv_sec = 0;
	ttimeval.tv_usec = _TimeOut * 1000;

	fd_set ReadSetTmp = ptSelectData->ReadFdSet;
	fd_set WriteSetTmp = ptSelectData->WriteFdSet;
	int nRtn = select(ptSelectData->MaxClientFd + 1, &ReadSetTmp, &WriteSetTmp, NULL, &ttimeval);
	if (nRtn == -1)
	{
		perror("select failed");
		return -1;
	}

	for (int i = 0; i <= ptSelectData->MaxClientFd; i++)
	{
		if (FD_ISSET(i, &ReadSetTmp))
		{
			//读数据
			EventActivate(_EventLoop_Info, i, READEVENT);
		}

		if (FD_ISSET(i, &WriteSetTmp))
		{
			//写数据
			EventActivate(_EventLoop_Info, i, WRITEEVENT);
		}

	}

	return 0;
}

static int SelectClear(PEVENTLOOP_INFO _EventLoop_Info)
{
	PSELECTDATA ptSelectData = (PSELECTDATA)_EventLoop_Info->pDispatcherData;

	free(ptSelectData);
	_EventLoop_Info->pDispatcherData = NULL;

	return 0;
}
