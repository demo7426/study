//�ļ�������
//      ʵ��һ��List����
//���ߣ�Ǯ��
//ʱ�䣺2024/2/23
//�޸ļ�¼��
//      2024/2/23     �½�

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

	//������ĩβ��ӽڵ�
	PNODE PushBack(std::string _Data);

	//�������ײ���ӽڵ�
	PNODE PushFront(std::string _Data);

	//���������ڵ�
	PNODE Insert(PNODE _pNode, std::string _Data);

	/// <summary>
	/// ��ȡ������ʵ��ָ�����
	/// </summary>
	/// <param name="_IsReverse"></param>
	/// <returns></returns>
	CAbstractIterator* GetIteratorInstance(bool _IsReverse = true);
private:
	PNODE m_ptHead = nullptr;		//ͷ�ڵ�
	PNODE m_ptTail = nullptr;		//β�ڵ�
	int m_nCount = 0;				//����ڵ�����
};

