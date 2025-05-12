/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	AsioIOThreadPool.h
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
	/// 使用轮询的方式获取对应的 io_context
	/// </summary>
	/// <returns></returns>
	boost::asio::io_context& GetIOContext();

	/// <summary>
	/// 停止IOServeicePool内部所有的IOContext运行
	/// </summary>
	/// <param name=""></param>
	void Stop(void);

private:
	IOContext m_cIOContext;
	Work m_cWork;										//用于保证 io_context 在未注册socket事件时不会退出其run()函数内部的循环
	std::vector<std::thread> m_vecWorkThread;
	std::size_t m_unNextIndex_IOContext = 0;
};


