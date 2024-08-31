//�ļ�������
//      ʵ��һ��Epoll��Ӧ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/19
//�޸ļ�¼��
//      2024/1/19     �½�
#include <stdlib.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string.h>

#include "Dispatcher.h"

#define MAX_EVENTS_NUM 512		//epoll���ʱ����󷵻�ʱ������

typedef	struct _EPOLLDATA
{
	int EpFd;
	struct epoll_event* Events;
}EPOLLDATA, *PEPOLLDATA;

//epoll��ʼ��
static void* EpollInit();
//epoll���
static int EpollAdd(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//epollɾ��
static int EpollDelete(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//epoll�޸�
static int EpollModify(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//epoll�¼����
static int EpollDispatch(PEVENTLOOP_INFO _EventLoop_Info, int _TimeOut);
//epoll�������(�ر�fd���ͷ��ڴ�)
static int EpollClear(PEVENTLOOP_INFO _EventLoop_Info);

static int EpollCtl(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info, int _Op);

struct _DISPATCHR_INFO g_tEpollDis_Info = {
	EpollInit, EpollAdd, EpollDelete, EpollModify, EpollDispatch, EpollClear
};

static void* EpollInit()
{
	PEPOLLDATA ptEpollData = (PEPOLLDATA)malloc(sizeof(EPOLLDATA));
	if (ptEpollData == NULL)
	{
		perror("EpollInit malloc failed");
		return NULL;
	}

	ptEpollData->EpFd = epoll_create(10);
	if (ptEpollData->EpFd == -1)
	{
		free(ptEpollData);
		perror("EpollInit epoll_create failed");
		return NULL;
	}

	ptEpollData->Events = (struct epoll_event*)calloc(MAX_EVENTS_NUM, sizeof(struct epoll_event));
	if (ptEpollData->Events == NULL)
	{
		close(ptEpollData->EpFd);
		perror("EpollInit calloc failed");
		return NULL;
	}

	return ptEpollData;
}

static int EpollAdd(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info)
{
	return EpollCtl(_Channel_Info, _EventLoop_Info, EPOLL_CTL_ADD);
}

static int EpollDelete(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info)
{
	int nRtn = EpollCtl(_Channel_Info, _EventLoop_Info, EPOLL_CTL_DEL);

	_Channel_Info->DestroyCallBack(_Channel_Info->Arg);

	return nRtn;
}

static int EpollModify(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info)
{
	return EpollCtl(_Channel_Info, _EventLoop_Info, EPOLL_CTL_MOD);
}

static int EpollDispatch(PEVENTLOOP_INFO _EventLoop_Info, int _TimeOut)
{
	PEPOLLDATA ptChannel_Info = (PEPOLLDATA)_EventLoop_Info->pDispatcherData;
	int nNum = epoll_wait(ptChannel_Info->EpFd, ptChannel_Info->Events, MAX_EVENTS_NUM, _TimeOut);

	for (int i = 0; i < nNum; i++)
	{
		int nEvent = ptChannel_Info->Events[i].events;
		int nFd = ptChannel_Info->Events[i].data.fd;
		if (nEvent & EPOLLERR || nEvent & EPOLLHUP)
		{
			//�ͻ��˶Ͽ�����
			EpollDelete(_EventLoop_Info->pChMap_Info, _EventLoop_Info);
		}

		if (nEvent & EPOLLIN)	//��ȡ����
		{
			EventActivate(_EventLoop_Info, nFd, READEVENT);
		}

		if (nEvent & EPOLLOUT)	//д������
		{
			EventActivate(_EventLoop_Info, nFd, WRITEEVENT);
		}
	}

	return 0;
}

static int EpollClear(PEVENTLOOP_INFO _EventLoop_Info)
{
	PEPOLLDATA ptChannel_Info = (PEPOLLDATA)_EventLoop_Info->pDispatcherData;

	free(ptChannel_Info->Events);
	close(ptChannel_Info->EpFd);
	free(ptChannel_Info);
	_EventLoop_Info->pDispatcherData = NULL;
}

static int EpollCtl(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info, int _Op)
{
	PEPOLLDATA ptChannel_Info = (PEPOLLDATA)_EventLoop_Info->pDispatcherData;
	struct epoll_event tepoll_event;
	memset(&tepoll_event, 0, sizeof tepoll_event);

	if (_Channel_Info->Events & READEVENT)
		tepoll_event.events |= EPOLLIN;
	if (_Channel_Info->Events & WRITEEVENT)
		tepoll_event.events |= EPOLLOUT;
	tepoll_event.data.fd = _Channel_Info->Fd;

	return epoll_ctl(ptChannel_Info->EpFd, _Op, _Channel_Info->Fd, &tepoll_event);
}