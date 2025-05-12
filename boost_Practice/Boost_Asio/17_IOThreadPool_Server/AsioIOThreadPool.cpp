/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	AsioIOThreadPool.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.05.12
��  ��: ʵ��һ��IOThreadPool
��  ע: ������1�� boost::asio::io_context��������벻ͬ���߳�������
�޸ļ�¼:

  1.  ����: 2025.05.12
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

*************************************************/

#include "AsioIOThreadPool.h"

CAsioIOThreadPool::CAsioIOThreadPool(std::size_t _ThreadSize) : 
	//Work����û��Ĭ�Ϲ��캯����������ʱ�������̰�һ�� executor���� io_context.get_executor()��,������ڳ�ʼ���б��н��г�ʼ������
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
