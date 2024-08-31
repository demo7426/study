#pragma once

//重载大于4字节的类操作符
namespace OverloadsClassOperators_GreaterThan4Bytes 
{
	//内存池技术改进，实现一个内存池通用类
	class CMyAllocate
	{
	public:
		CMyAllocate();
		~CMyAllocate();

		/// <summary>
		/// 分配内存空间
		/// </summary>
		/// <param name="_Size"></param>
		/// <returns></returns>
		void* AllocateSpace(size_t _Size);

		/// <summary>
		/// 释放内存空间
		/// </summary>
		/// <param name="_Head"></param>
		void DeleteSpace(void* _Head);

		static size_t m_unNewCount;//调用new的次数
		static size_t m_unMallocCount;//调用malloc的次数

		typedef struct _EMBEDDED_INFO//嵌入式结构体
		{
			_EMBEDDED_INFO* ptNext;//嵌入式结构体指针

		}EMBEDDED_INFO, * PEMBEDDED_INFO;
	private:
		EMBEDDED_INFO* m_ptCanAllocMemory = nullptr;//可以分配的内存地址
		static size_t m_unMemoryMul;//分配内存块的大小为该类的倍数
	};

	//测试上面的内存池类
	class CTestMemoryPool
	{
	public:
		CTestMemoryPool();
		~CTestMemoryPool();

		int m_nValue1;
		int m_nValue2;//保证该类字节数大于4字节

		static void* operator new(size_t _Size);
		static void operator delete(void* _Head);
	private:
		static CMyAllocate m_cMyAllocate;
		
	};

	//测试内存池函数
	void Test02();
}