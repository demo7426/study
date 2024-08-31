//�ļ�������
//      ʵ��һ��Epoll��Ӧ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/19
//�޸ļ�¼��
//      2024/1/19     �½�
#include <stdlib.h>
#include <sys/epoll.h>
#include "Dispatcher.h"

typedef	struct _EPOLLDATA
{
	int EpFd;
	struct epoll_event* Events;
}EPOLLDATA, *PEPOLLDATA;

//��ʼ��
static void* EpollInit();
//���
static int EpollAdd(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//ɾ��
static int EpollDelete(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//�޸�
static int EpollModify(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//�¼����
static int EpollDispatch(PEVENTLOOP_INFO _EventLoop_Info, int _TimeOut);
//�������(�ر�fd���ͷ��ڴ�)
static int EpollClear();

DISPATCHR_INFO g_tDispatcher_Info = {
	EpollInit, EpollAdd, EpollDelete, EpollModify, EpollDispatch, EpollClear
};

static void* EpollInit()
{

}

static int EpollAdd(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
static int EpollDelete(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
static int EpollModify(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
static int EpollDispatch(PEVENTLOOP_INFO _EventLoop_Info, int _TimeOut);
static int EpollClear();