#include"OverloadsClassOperators_GreaterThan4Bytes.h"

using namespace OverloadsClassOperators_GreaterThan4Bytes;

size_t CMyAllocate::m_unNewCount = 0;//调用new的次数
size_t CMyAllocate::m_unMallocCount = 0;//调用malloc的次数
size_t CMyAllocate::m_unMemoryMul = 5;;//分配内存块的大小为该类的倍数

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

	if (m_ptCanAllocMemory == nullptr)//如果内存池没有空间了，向操作系统申请新的内存空间
	{
		m_ptCanAllocMemory = reinterpret_cast<EMBEDDED_INFO*>(new char[_Size * m_unMemoryMul]);
		ptTemp = m_ptCanAllocMemory;

		while (ptTemp != &m_ptCanAllocMemory[_Size - 1])//将分配出来的内存空间链接到一起
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
