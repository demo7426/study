/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	TaskQueue.cpp
��  ��:	Ǯ��      �汾: V1.0.0     �½�����: 2024.07.06
��  ��: ʹ��STL������װһ���������
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

