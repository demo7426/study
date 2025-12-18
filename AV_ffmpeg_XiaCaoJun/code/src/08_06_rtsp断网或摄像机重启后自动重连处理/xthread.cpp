/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xthread.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.14
描  述: 线程类实现
备  注:
修改记录:

  1.  日期: 2025.12.14
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include "xthread.h"
#include "Debug.h"

CXThread::~CXThread()
{
}

int CXThread::Start(void)
{
	std::lock_guard<std::mutex> lock(m_cMut);

	if (m_IsExit == false)
	{
		DEBUG(DEBUG_LEVEL_WARN, "线程已经启动");
		return -2;
	}

	m_IsExit = false;
	
	m_cThread = std::thread(&CXThread::Main, this);
	
	DEBUG(DEBUG_LEVEL_INFO, "CXThread::Start()");

	return 0;
}

void CXThread::Stop(void)
{
	{
		std::lock_guard<std::mutex> lock(m_cMut);

		m_IsExit = true;
	}

	if (m_cThread.joinable())
		m_cThread.join();

	DEBUG(DEBUG_LEVEL_INFO, "CXThread::Stop()");
}
