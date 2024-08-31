//文件描述：
//      实现一个iterator容器
//作者：钱锐
//时间：2024/2/23
//修改记录：
//      2024/2/23     新建

#pragma once
#include "List.h"

//遍历迭代器
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

//正序遍历迭代器
class CForwardIterator: public CAbstractIterator
{
public:
	using CAbstractIterator::CAbstractIterator;

	void Next() override;
	PNODE First() override;
	PNODE End() override;
};

//逆序遍历迭代器
class CReverseIterator: public CAbstractIterator
{
public:
	using CAbstractIterator::CAbstractIterator;

	void Next() override;
	PNODE First() override;
	PNODE End() override;
};


