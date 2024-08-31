//文件描述：
//      实现一个PollDispatcher模块
//作者：钱锐
//时间：2024/2/18
//修改记录：
//      2024/2/18     新建

#pragma once
#include <poll.h>
#include "Dispatcher.h"

class CPollDispatcher : public CDispatcher
{
public:
	CPollDispatcher() = delete;
	CPollDispatcher(const CPollDispatcher&) = delete;
	CPollDispatcher(CEventLoop* _EventLoop_Info);
	~CPollDispatcher();

	//添加
	int Add() override;
	//删除
	int Delete() override;
	//修改
	int Modify() override;
	//事件监测 _TimeOut：单位为毫秒
	int Dispatch(int _TimeOut = 2000) override;

private:
	static const int m_nMaxNum = 512;					//poll检测时，最大客户端连接数量
	int m_nMaxClientFdIndex;							//最大有效客户端文件描述符所在索引位置
	struct pollfd m_tPollfds[m_nMaxNum];
};
