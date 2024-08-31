//文件描述：
//      将实现一个调度程序模块 其中包括select、pool、epoll三种模型
//作者：钱锐
//时间：2024/2/18
//修改记录：
//      2024/2/18     新建

#pragma once
#include <string>
#include "Channel.h"
#include "EventLoop.h"

class CEventLoop;
class CDispatcher
{
public:
	CDispatcher() = delete;
	CDispatcher(const CDispatcher&) = delete;
	CDispatcher(CEventLoop* _EventLoop_Info);
	virtual ~CDispatcher();

	//添加
	virtual int Add() = 0;
	//删除
	virtual int Delete() = 0;
	//修改
	virtual int Modify() = 0;
	//事件监测 _TimeOut：单位为毫秒
	virtual int Dispatch(int _TimeOut = 2000) = 0;

	inline void SetChannel(CChannel* _pChannnel)
	{
		m_pcChannel = _pChannnel;
	}

protected:
	CChannel* m_pcChannel;
	CEventLoop* m_pcEventLoop_Info;

	std::string m_strName = std::string();
};