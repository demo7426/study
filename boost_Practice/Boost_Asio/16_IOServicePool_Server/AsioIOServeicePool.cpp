/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	AsioIOServeicePool.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.05.10
��  ��: ʵ��һ��IOServeicePool
��  ע:
�޸ļ�¼:

  1.  ����: 2025.05.10
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

*************************************************/

#include "AsioIOServeicePool.h"

CAsioIOServeicePool::CAsioIOServeicePool(std::size_t _ThreadSize): m_vecIOContexts(_ThreadSize), m_unNextIndex_IOContext(0)
{
	for (size_t i = 0; i < m_vecIOContexts.size(); i++)
	{
		m_vecWorks.push_back(boost::asio::make_work_guard(m_vecIOContexts[i]));
	}
	
	//�������io_context����������̣߳�ÿ���߳��ڲ�������io_context
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
