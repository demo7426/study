//�ļ�������
//      ʵ��һ��iterator����
//���ߣ�Ǯ��
//ʱ�䣺2024/2/23
//�޸ļ�¼��
//      2024/2/23     �½�

#pragma once
#include "List.h"

//����������
class CAbstractIterator
{
public:
	CAbstractIterator(CList* _pList): m_pcList(_pList){}
	
	inline PNODE GetCurNode()
	{
		return m_ptNode;
	}

	virtual void Next() = 0;
	virtual PNODE First() = 0;
	virtual PNODE End() = 0;
protected:
	PNODE m_ptNode = nullptr;
	CList* m_pcList = nullptr;

};

//�������������
class CForwardIterator: public CAbstractIterator
{
public:
	using CAbstractIterator::CAbstractIterator;

	void Next() override;
	PNODE First() override;
	PNODE End() override;
};

//�������������
class CReverseIterator: public CAbstractIterator
{
public:
	using CAbstractIterator::CAbstractIterator;

	void Next() override;
	PNODE First() override;
	PNODE End() override;
};


