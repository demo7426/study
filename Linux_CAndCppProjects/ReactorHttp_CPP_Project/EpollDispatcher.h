//文件描述：
//      实现一个EpollDispatcher模块
//作者：钱锐
//时间：2024/2/18
//修改记录：
//      2024/2/18     新建

#pragma once
#include <sys/epoll.h>
#include "Dispatcher.h"

class CEpollDispatcher: public CDispatcher
{
public:
	CEpollDispatcher() = delete;
	CEpollDispatcher(const CEpollDispatcher&) = delete;
	CEpollDispatcher(CEventLoop* _EventLoop_Info);
	~CEpollDispatcher();

	//添加
	int Add() override;
	//删除
	int Delete() override;
	//修改
	int Modify() override;
	//事件监测 _TimeOut：单位为毫秒
	int Dispatch(int _TimeOut = 2000) override;

private:
	const int m_nMaxNum = 512;				//epoll检测时，最大返回时间数量
	int m_nEpFd;							//Epoll根节点
	struct epoll_event* m_pcEvents;			//epoll检测时，返回数据

private:
	int EpollCtl(int _Op);
};

