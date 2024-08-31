//文件描述：
//      实现一个SelectDispatcher模块
//作者：钱锐
//时间：2024/2/19
//修改记录：
//      2024/2/19     新建

#pragma once
#include <sys/select.h>
#include "Dispatcher.h"

class CSelectDispatcher : public CDispatcher
{
public:
	CSelectDispatcher() = delete;
	CSelectDispatcher(const CSelectDispatcher&) = delete;
	CSelectDispatcher(CEventLoop* _EventLoop_Info);
	~CSelectDispatcher();
	
	//添加
	int Add() override;
	//删除
	int Delete() override;
	//修改
	int Modify() override;
	//事件监测 _TimeOut：单位为毫秒
	int Dispatch(int _TimeOut = 2000) override;

private:
	int m_nMaxClientFd;			//最大有效客户端文件描述符
	fd_set m_tReadFdSet;
	fd_set m_tWriteFdSet;
};
