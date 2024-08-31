#include"Overload_NewAndDeleteOperators.h"
using namespace Overload_NewAndDeleteOperators;

CTeacher::CTeacher()
{
}

CTeacher::~CTeacher()
{
}

size_t CTeacher::m_unNewCount = 0;//调用new的次数
size_t CTeacher::m_unMallocCount = 0;//调用malloc的次数
CTeacher* CTeacher::m_pcCanAllocMemory = nullptr;//可以分配的内存地址
size_t CTeacher::m_unMemoryMul = 100;//分配内存块的大小为该类的倍数

//#define _QR_Test

void* CTeacher::operator new(size_t _Size)
{
//#ifdef _QR_Test
//	return reinterpret_cast<CTeacher*>(new char[sizeof(CTeacher)]);
//#endif // _QR_Test

	CTeacher* pcTeacher = nullptr;

	if (!m_pcCanAllocMemory)//如果之前分配的内存空间已经使用完毕
	{
		m_pcCanAllocMemory = reinterpret_cast<CTeacher*>(new char[_Size * m_unMemoryMul]);//向操作系统申请内存
		pcTeacher = m_pcCanAllocMemory;

		while (pcTeacher!= &m_pcCanAllocMemory[m_unMemoryMul - 1])//将分配好的内存链接起来，供后续分配使用
		{
			pcTeacher->m_pcNext = pcTeacher + 1;
			pcTeacher++;
		}

		pcTeacher->m_pcNext = nullptr;
		m_unMallocCount++;
	}

	pcTeacher = m_pcCanAllocMemory;
	m_pcCanAllocMemory = m_pcCanAllocMemory->m_pcNext;

	m_unNewCount++;
	return pcTeacher;
}

void CTeacher::operator delete(void* _Ptr)
{
	(static_cast<CTeacher*>(_Ptr))->m_pcNext = m_pcCanAllocMemory;
	m_pcCanAllocMemory = static_cast<CTeacher*>(_Ptr);
}
