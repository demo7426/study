/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	TaskQueue.h
��  ��:	Ǯ��      �汾: V1.0.0     �½�����: 2024.07.06
��  ��: ʹ��STL������װһ��������У�֧�������ߺ�������ģ��
��  ע:	condition_variable_any ����֧�����е�������
�޸ļ�¼:

  1.  ����: 2024.07.06
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V1.0.0

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
	/// �������
	/// </summary>
	/// <param name="_Arg"></param>
	/// <returns>-2--ִ��ʧ�ܣ�-1--��������0--ִ�гɹ�</returns>
	int Push_Back(void* _pArg);	

	/// <summary>
	/// ȡ�����ݣ�����ɾ��
	/// </summary>
	/// <param name="_Arg"></param>
	/// <returns>-2--ִ��ʧ�ܣ�-1--��������0--ִ�гɹ�</returns>
	int Pop_Front(void** _ppArg);

	/// <summary>
	/// ��ȡ��ǰ������еĴ�С
	/// </summary>
	/// <returns>-2--ִ��ʧ�ܣ�-1--��������0--ִ�гɹ�</returns>
	inline unsigned int GetCurSize()
	{
		std::lock_guard<std::mutex> cTaskLock(m_mtxTaskMutex);
		return m_queTask.size();
	}

	/// <summary>
	/// �Ƿ��;
	/// </summary>
	/// <returns>true--��;false--������</returns>
	inline bool IsEmpty()
	{
		std::lock_guard<std::mutex> cTaskLock(m_mtxTaskMutex);
		return m_queTask.empty();
	}

	/// <summary>
	/// �Ƿ���;
	/// </summary>
	/// <returns>true--��;false--δ��</returns>
	bool IsFull();

private:
	unsigned int m_unTaskCap = 0;					//��������������
	std::queue<void*> m_queTask;
	std::mutex m_mtxTaskMutex;						//������ж�ռ��	
	std::condition_variable_any m_condNotEmpty;			//��Ϊ�գ���������
	std::condition_variable_any m_condNotFull;			//��Ϊ������������
};

