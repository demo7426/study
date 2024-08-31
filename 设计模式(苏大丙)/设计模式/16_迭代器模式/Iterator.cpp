#include "Iterator.h"

void CForwardIterator::Next()
{
	if (m_ptNode == End())	//防止数据越界
		return;

	m_ptNode = m_ptNode->pNext;
}

PNODE CForwardIterator::First()
{
	m_ptNode = m_pcList->GetHead();
	return m_pcList->GetHead();
}

PNODE CForwardIterator::End()
{
	return m_pcList->GetTail()->pNext;
}

void CReverseIterator::Next()
{
	if (m_ptNode == End())	//防止数据越界
		return;

	m_ptNode = m_ptNode->pPrev;
	return;
}

PNODE CReverseIterator::First()
{
	m_ptNode = m_pcList->GetTail();
	return m_pcList->GetTail();
}

PNODE CReverseIterator::End()
{
	return m_pcList->GetHead()->pPrev;
}
