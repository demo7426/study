/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	TaskQueue.cpp
��  ��:	Ǯ��      �汾: V1.0.0     �½�����: 2024.07.06
��  ��: ʹ��STL������װһ��������У�֧�������ߺ�������ģ��
��  ע:
�޸ļ�¼:

  1.  ����: 2024.07.06
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V1.0.0

*************************************************/

#include "TaskQueue.h"

#define RTN_FAILURE			-2				//ִ��ʧ��
#define RTN_INPUTPAMERR		-1				//��������
#define RTN_SUCCESS			0				//ִ�гɹ�


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

	std::lock_guard<std::mutex> cTaskLock(m_mtxTaskMutex);			

	while (m_queTask.size() == m_unTaskCap)
	{
		m_condNotFull.wait(m_mtxTaskMutex);			//ͬ���߳�
	}

	m_queTask.push(_pArg);
	std::cout << "Push data: " << _pArg << ", this thread: " << std::this_thread::get_id() << '\n';
	m_condNotEmpty.notify_one();				//�����������߳�

	return RTN_SUCCESS;
}

int CTaskQueue::Pop_Front(void** _ppArg)
{
	if (_ppArg == nullptr)
	{
		return RTN_INPUTPAMERR;
	}

	std::unique_lock<std::mutex> cTaskLock(m_mtxTaskMutex);

	while (m_queTask.empty())
	{
		m_condNotEmpty.wait(cTaskLock);			//ͬ���߳�
	}

	*_ppArg = m_queTask.front();
	m_queTask.pop();
	std::cout << "Take data: " << *_ppArg << ", this thread: " << std::this_thread::get_id() << '\n';

	m_condNotFull.notify_one();					//�����������߳�

	return RTN_SUCCESS;
}

bool CTaskQueue::IsFull()
{
	std::lock_guard<std::mutex> cTaskLock(m_mtxTaskMutex);

	if (m_queTask.size() == m_unTaskCap)
		return true;
	return false;

}

