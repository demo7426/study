/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	AsioIOServeicePool.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.05.10
��  ��: ʵ��һ��IOServeicePool
��  ע: ��������� boost::asio::io_context��������벻ͬ���߳�������
�޸ļ�¼:

  1.  ����: 2025.05.10
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

class CAsioIOServeicePool : public CSingleton<CAsioIOServeicePool>
{
	friend class  CSingleton<CAsioIOServeicePool>;
private:
	CAsioIOServeicePool(std::size_t _ThreadSize = std::thread::hardware_concurrency());

public:
	CAsioIOServeicePool(const CAsioIOServeicePool&) = delete;
	CAsioIOServeicePool& operator = (const CAsioIOServeicePool&) = delete;

	~CAsioIOServeicePool();

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
	std::vector<IOContext> m_vecIOContexts;
	std::vector<Work> m_vecWorks;				//���ڱ�֤ io_context ��δע��socket�¼�ʱ�����˳���run()�����ڲ���ѭ��
	std::vector<std::thread> m_vecWorkThread;
	std::size_t m_unNextIndex_IOContext;
};


