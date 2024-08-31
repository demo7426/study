#include "List.h"
#include "Iterator.h"

PNODE CList::PushBack(std::string _Data)
{
	PNODE ptNode = new NODE(_Data);
	if (m_ptHead == nullptr)
	{
		m_ptHead = m_ptTail = ptNode;
	}
	else
	{
		ptNode->pPrev = m_ptTail;
		m_ptTail->pNext = ptNode;
		m_ptTail = ptNode;
	}
	m_nCount++;
	return ptNode;
}

PNODE CList::PushFront(std::string _Data)
{
	PNODE ptNode = new NODE(_Data);
	if (m_ptHead == nullptr)
	{
		m_ptHead = m_ptTail = ptNode;
	}
	else
	{
		ptNode->pNext = m_ptHead;
		m_ptHead->pPrev = ptNode;
		m_ptHead = ptNode;
	}
	m_nCount++;
	return ptNode;
}

PNODE CList::Insert(PNODE _pNode, std::string _Data)
{
	PNODE ptNode = nullptr;
	if (_pNode == m_ptHead)
		ptNode = PushBack(_Data);
	else
	{
		ptNode = new NODE(_Data);

		ptNode->pNext = _pNode;
		ptNode->pPrev = _pNode->pPrev;

		_pNode->pPrev->pNext = ptNode;
		_pNode->pPrev = ptNode;
		
		m_nCount++;
	}

	return ptNode;
}

CAbstractIterator* CList::GetIteratorInstance(bool _IsReverse)
{
	CAbstractIterator* pcAbstractIterator = nullptr;

	if (_IsReverse)
		pcAbstractIterator = new CReverseIterator(this);
	else
		pcAbstractIterator = new CForwardIterator(this);

	return pcAbstractIterator;
}

