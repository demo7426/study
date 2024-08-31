//文件描述：
//      实现一个List容器
//作者：钱锐
//时间：2024/2/23
//修改记录：
//      2024/2/23     新建

#pragma once
#include <string>

class CAbstractIterator;

typedef struct _NODE
{
	_NODE(std::string _Data)
	{
		Data = _Data;
	}

	struct _NODE* pPrev;
	std::string Data;
	struct _NODE* pNext;
}NODE, *PNODE;

class CList
{
public:
	inline PNODE GetHead()
	{
		return m_ptHead;
	}
	
	inline PNODE GetTail()
	{
		return m_ptTail;
	}
	
	inline int GetCount()
	{
		return m_nCount;
	}

	//向链表末尾添加节点
	PNODE PushBack(std::string _Data);

	//向链表首部添加节点
	PNODE PushFront(std::string _Data);

	//向链表插入节点
	PNODE Insert(PNODE _pNode, std::string _Data);

	/// <summary>
	/// 获取迭代器实例指针对象
	/// </summary>
	/// <param name="_IsReverse"></param>
	/// <returns></returns>
	CAbstractIterator* GetIteratorInstance(bool _IsReverse = true);
private:
	PNODE m_ptHead = nullptr;		//头节点
	PNODE m_ptTail = nullptr;		//尾节点
	int m_nCount = 0;				//链表节点数量
};

