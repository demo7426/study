#include"OverloadsClassOperators_GreaterThan4Bytes.h"

using namespace OverloadsClassOperators_GreaterThan4Bytes;

size_t CMyAllocate::m_unNewCount = 0;//����new�Ĵ���
size_t CMyAllocate::m_unMallocCount = 0;//����malloc�Ĵ���
size_t CMyAllocate::m_unMemoryMul = 5;;//�����ڴ��Ĵ�СΪ����ı���

CMyAllocate CTestMemoryPool::m_cMyAllocate;

CMyAllocate::CMyAllocate()
{
}

CMyAllocate::~CMyAllocate()
{
}

CTestMemoryPool::CTestMemoryPool()
{
}

CTestMemoryPool::~CTestMemoryPool()
{
}

void* CMyAllocate::AllocateSpace(size_t _Size)
{
	EMBEDDED_INFO* ptTemp = nullptr;

	if (m_ptCanAllocMemory == nullptr)//����ڴ��û�пռ��ˣ������ϵͳ�����µ��ڴ�ռ�
	{
		m_ptCanAllocMemory = reinterpret_cast<EMBEDDED_INFO*>(new char[_Size * m_unMemoryMul]);
		ptTemp = m_ptCanAllocMemory;

		while (ptTemp != &m_ptCanAllocMemory[_Size - 1])//������������ڴ�ռ����ӵ�һ��
		{
			ptTemp->ptNext = ptTemp + 1;
			ptTemp++;
		}

		ptTemp->ptNext = nullptr;
		m_unMallocCount++;
	}

	ptTemp = m_ptCanAllocMemory;
	m_ptCanAllocMemory = m_ptCanAllocMemory->ptNext;
	m_unNewCount++;

	return ptTemp;
}

void CMyAllocate::DeleteSpace(void* _Head)
{
	(static_cast<EMBEDDED_INFO*>(_Head))->ptNext = m_ptCanAllocMemory;
	m_ptCanAllocMemory = static_cast<EMBEDDED_INFO*> (_Head);
}

void* CTestMemoryPool::operator new(size_t _Size)
{
	return m_cMyAllocate.AllocateSpace(_Size);
}

void CTestMemoryPool::operator delete(void* _Head)
{
	m_cMyAllocate.DeleteSpace(_Head);
}

void OverloadsClassOperators_GreaterThan4Bytes::Test02()
{
	for (size_t i = 0; i < 5000'000; i++)
	{
		CTestMemoryPool* pcTestMemoryPool = new CTestMemoryPool();
	}
}
