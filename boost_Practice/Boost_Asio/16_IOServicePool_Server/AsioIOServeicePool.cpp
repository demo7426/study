/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	AsioIOServeicePool.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.05.10
描  述: 实现一个IOServeicePool
备  注:
修改记录:

  1.  日期: 2025.05.10
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#include "AsioIOServeicePool.h"

CAsioIOServeicePool::CAsioIOServeicePool(std::size_t _ThreadSize): m_vecIOContexts(_ThreadSize), m_unNextIndex_IOContext(0)
{
	for (size_t i = 0; i < m_vecIOContexts.size(); i++)
	{
		m_vecWorks.push_back(boost::asio::make_work_guard(m_vecIOContexts[i]));
	}
	
	//遍历多个io_context，创建多个线程，每个线程内部都启动io_context
	for (size_t i = 0; i < m_vecIOContexts.size(); i++)
	{
		m_vecWorkThread.emplace_back([this, i]() {
			m_vecIOContexts[i].run();
			});
	}
}

CAsioIOServeicePool::~CAsioIOServeicePool()
{
	std::cout << __FUNCTION__ << std::endl;
}

boost::asio::io_context& CAsioIOServeicePool::GetIOContext()
{
	auto& cIOContext = m_vecIOContexts[m_unNextIndex_IOContext];

	m_unNextIndex_IOContext = m_unNextIndex_IOContext % m_vecIOContexts.size();
	m_unNextIndex_IOContext++;

	return cIOContext;
}

void CAsioIOServeicePool::Stop(void)
{
	for (auto& cWork : m_vecWorks)
	{
		cWork.reset();
	}

	for (auto& cThread : m_vecWorkThread)
	{
		cThread.join();
	}
}
