/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	AsioIOThreadPool.h
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

#pragma once

#include <iostream>
#include <thread>
#include <vector>

#include "boost/asio.hpp"

#include "Singleton.h"

class CAsioIOThreadPool : public CSingleton<CAsioIOThreadPool>
{
	friend class CSingleton<CAsioIOThreadPool>;
private:
	CAsioIOThreadPool(std::size_t _ThreadSize = std::thread::hardware_concurrency());

public:
	CAsioIOThreadPool(const CAsioIOThreadPool&) = delete;
	CAsioIOThreadPool& operator = (const CAsioIOThreadPool&) = delete;

	~CAsioIOThreadPool();

	using IOContext = boost::asio::io_context;
	using Work = boost::asio::executor_work_guard<boost::asio::io_context::executor_type, void, void>;
	using WorkPtr = std::unique_ptr<Work>;

	/// <summary>
	/// ʹ����ѯ�ķ�ʽ��ȡ��Ӧ�� io_context
	/// </summary>
	/// <returns></returns>
	boost::asio::io_context& GetIOContext();

	/// <summary>
	/// ֹͣIOServeicePool�ڲ����е�IOContext����
	/// </summary>
	/// <param name=""></param>
	void Stop(void);

private:
	IOContext m_cIOContext;
	Work m_cWork;										//���ڱ�֤ io_context ��δע��socket�¼�ʱ�����˳���run()�����ڲ���ѭ��
	std::vector<std::thread> m_vecWorkThread;
	std::size_t m_unNextIndex_IOContext = 0;
};


