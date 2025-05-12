/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	AsioIOThreadPool.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.05.12
描  述: 实现一个IOThreadPool
备  注: 创建出1个 boost::asio::io_context，将其放入不同的线程中运行
修改记录:

  1.  日期: 2025.05.12
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#include "AsioIOThreadPool.h"

CAsioIOThreadPool::CAsioIOThreadPool(std::size_t _ThreadSize) : 
	//Work类型没有默认构造函数，创建它时必须立刻绑定一个 executor（即 io_context.get_executor()）,必须放在初始化列表中进行初始化操作
	m_cWork(boost::asio::make_work_guard(m_cIOContext))		
{
	for (size_t i = 0; i < _ThreadSize; i++)
	{
		m_vecWorkThread.emplace_back([this]() {
			m_cIOContext.run();
			});
	}
}

CAsioIOThreadPool::~CAsioIOThreadPool()
{
	std::cout << __FUNCTION__ << std::endl;
}

boost::asio::io_context& CAsioIOThreadPool::GetIOContext()
{
	return m_cIOContext;
}

void CAsioIOThreadPool::Stop(void)
{
	m_cWork.reset();

	for (auto& it : m_vecWorkThread)
	{
		if (it.joinable())
			it.join();
	}
}
