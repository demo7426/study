#pragma once
#include<iostream>

using namespace std;

namespace Overload_NewAndDeleteOperators
{
	class CTeacher
	{
	public:
		CTeacher();
		~CTeacher();

		/// <summary>
		/// ����new������
		/// </summary>
		/// <param name="_Size"></param>
		/// <returns></returns>
		static void* operator new(size_t _Size);

		/// <summary>
		/// ����delete������
		/// </summary>
		/// <param name="_Head"></param>
		static void operator delete(void* _Ptr);

		static size_t m_unNewCount;//����new�Ĵ���
		static size_t m_unMallocCount;//����malloc�Ĵ���
	private:
		CTeacher* m_pcNext;
		static CTeacher* m_pcCanAllocMemory;//���Է�����ڴ��ַ
		static size_t m_unMemoryMul;//�����ڴ��Ĵ�СΪ����ı���
	};
}



