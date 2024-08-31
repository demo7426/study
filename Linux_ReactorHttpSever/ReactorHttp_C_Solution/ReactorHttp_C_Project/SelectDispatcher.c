//�ļ�������
//      ʵ��һ��Select��Ӧ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/21
//�޸ļ�¼��
//      2024/1/21     �½�
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

#include "Dispatcher.h"

typedef	struct _SELECTDATA
{
	int MaxClientFd;			//�����Ч�ͻ����ļ�������
	fd_set ReadFdSet;
	fd_set WriteFdSet;
}SELECTDATA, * PSELECTDATA;

//select��ʼ��
static void* SelectInit();
//select���
static int SelectAdd(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//selectɾ��
static int SelectDelete(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//select�޸�
static int SelectModify(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//select�¼����
static int SelectDispatch(PEVENTLOOP_INFO _EventLoop_Info, int _TimeOut);
//select�������(�ر�fd���ͷ��ڴ�)
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
			//������
			EventActivate(_EventLoop_Info, i, READEVENT);
		}

		if (FD_ISSET(i, &WriteSetTmp))
		{
			//д����
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
