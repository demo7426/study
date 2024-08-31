//文件描述：
//      实现一个Epoll反应堆
//作者：钱锐
//时间：2024/1/19
//修改记录：
//      2024/1/19     新建
#include <stdlib.h>
#include <sys/epoll.h>
#include "Dispatcher.h"

typedef	struct _EPOLLDATA
{
	int EpFd;
	struct epoll_event* Events;
}EPOLLDATA, *PEPOLLDATA;

//初始化
static void* EpollInit();
//添加
static int EpollAdd(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//删除
static int EpollDelete(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//修改
static int EpollModify(PCHANNEL_INFO _Channel_Info, PEVENTLOOP_INFO _EventLoop_Info);
//事件监测
static int EpollDispatch(PEVENTLOOP_INFO _EventLoop_Info, int _TimeOut);
//清除数据(关闭fd、释放内存)
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