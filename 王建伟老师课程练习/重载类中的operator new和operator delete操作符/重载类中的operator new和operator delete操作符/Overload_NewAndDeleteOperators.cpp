#include"Overload_NewAndDeleteOperators.h"
using namespace Overload_NewAndDeleteOperators;

CTeacher::CTeacher()
{
}

CTeacher::~CTeacher()
{
}

size_t CTeacher::m_unNewCount = 0;//����new�Ĵ���
size_t CTeacher::m_unMallocCount = 0;//����malloc�Ĵ���
CTeacher* CTeacher::m_pcCanAllocMemory = nullptr;//���Է�����ڴ��ַ
size_t CTeacher::m_unMemoryMul = 100;//�����ڴ��Ĵ�СΪ����ı���

//#define _QR_Test

void* CTeacher::operator new(size_t _Size)
{
//#ifdef _QR_Test
//	return reinterpret_cast<CTeacher*>(new char[sizeof(CTeacher)]);
//#endif // _QR_Test

	CTeacher* pcTeacher = nullptr;

	if (!m_pcCanAllocMemory)//���֮ǰ������ڴ�ռ��Ѿ�ʹ�����
	{
		m_pcCanAllocMemory = reinterpret_cast<CTeacher*>(new char[_Size * m_unMemoryMul]);//�����ϵͳ�����ڴ�
		pcTeacher = m_pcCanAllocMemory;

		while (pcTeacher!= &m_pcCanAllocMemory[m_unMemoryMul - 1])//������õ��ڴ���������������������ʹ��
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
