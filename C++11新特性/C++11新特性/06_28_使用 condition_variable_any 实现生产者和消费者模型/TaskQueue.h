/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	TaskQueue.h
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.06
描  述: 使用STL容器封装一个任务队列，支持生产者和消费者模型
备  注:	condition_variable_any 可以支持所有的锁类型
修改记录:

  1.  日期: 2024.07.06
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/
#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

class CTaskQueue
{
public:
	explicit CTaskQueue(const unsigned int _Capcity)  noexcept;
	CTaskQueue(CTaskQueue&) = delete;
	CTaskQueue(CTaskQueue&&) = delete;

	CTaskQueue& operator=(CTaskQueue&) = delete;
	CTaskQueue& operator=(CTaskQueue&&) = delete;

	~CTaskQueue();

	/// <summary>
	/// 添加数据
	/// </summary>
	/// <param name="_Arg"></param>
	/// <returns>-2--执行失败；-1--参数错误；0--执行成功</returns>
	int Push_Back(void* _pArg);	

	/// <summary>
	/// 取出数据，并且删除
	/// </summary>
	/// <param name="_Arg"></param>
	/// <returns>-2--执行失败；-1--参数错误；0--执行成功</returns>
	int Pop_Front(void** _ppArg);

	/// <summary>
	/// 获取当前任务队列的大小
	/// </summary>
	/// <returns>-2--执行失败；-1--参数错误；0--执行成功</returns>
	inline unsigned int GetCurSize()
	{
		std::lock_guard<std::mutex> cTaskLock(m_mtxTaskMutex);
		return m_queTask.size();
	}

	/// <summary>
	/// 是否空;
	/// </summary>
	/// <returns>true--空;false--有数据</returns>
	inline bool IsEmpty()
	{
		std::lock_guard<std::mutex> cTaskLock(m_mtxTaskMutex);
		return m_queTask.empty();
	}

	/// <summary>
	/// 是否满;
	/// </summary>
	/// <returns>true--满;false--未满</returns>
	bool IsFull();

private:
	unsigned int m_unTaskCap = 0;					//任务队列最大容量
	std::queue<void*> m_queTask;
	std::mutex m_mtxTaskMutex;						//任务队列独占锁	
	std::condition_variable_any m_condNotEmpty;			//不为空，条件变量
	std::condition_variable_any m_condNotFull;			//不为满，条件变量
};

