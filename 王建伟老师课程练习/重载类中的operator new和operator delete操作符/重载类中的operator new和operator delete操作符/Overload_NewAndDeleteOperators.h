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
		/// 重载new操作符
		/// </summary>
		/// <param name="_Size"></param>
		/// <returns></returns>
		static void* operator new(size_t _Size);

		/// <summary>
		/// 重载delete操作符
		/// </summary>
		/// <param name="_Head"></param>
		static void operator delete(void* _Ptr);

		static size_t m_unNewCount;//调用new的次数
		static size_t m_unMallocCount;//调用malloc的次数
	private:
		CTeacher* m_pcNext;
		static CTeacher* m_pcCanAllocMemory;//可以分配的内存地址
		static size_t m_unMemoryMul;//分配内存块的大小为该类的倍数
	};
}



