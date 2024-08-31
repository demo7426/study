/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	TaskQueue.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.06
描  述: 使用STL容器封装一个任务队列
备  注:
修改记录:

  1.  日期: 2024.07.06
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include "TaskQueue.h"

#define RTN_FAILURE			-2				//执行失败
#define RTN_INPUTPAMERR		-1				//参数错误
#define RTN_SUCCESS			0				//执行成功


CTaskQueue::CTaskQueue(const unsigned int _Capcity) noexcept : m_unTaskCap(_Capcity)
{
}

CTaskQueue::~CTaskQueue()
{
}

int CTaskQueue::Push_Back(void* _pArg)
{
	if (_pArg == nullptr)
	{
		return RTN_INPUTPAMERR;
	}

	if (m_queTask.size() < m_unTaskCap)
	{
		m_queTask.push(_pArg);
		return RTN_SUCCESS;
	}

	return RTN_FAILURE;
}

int CTaskQueue::Pop_Front(void** _ppArg)
{
	if (_ppArg == nullptr)
	{
		return RTN_INPUTPAMERR;
	}

	if (!m_queTask.empty())
	{
		*_ppArg = m_queTask.front();
		m_queTask.pop();
		return RTN_SUCCESS;
	}

	return 0;
}

bool CTaskQueue::IsFull()
{
	if (m_queTask.size() == m_unTaskCap)
		return true;
	return false;

}

