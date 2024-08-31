#pragma once

//���ش���4�ֽڵ��������
namespace OverloadsClassOperators_GreaterThan4Bytes 
{
	//�ڴ�ؼ����Ľ���ʵ��һ���ڴ��ͨ����
	class CMyAllocate
	{
	public:
		CMyAllocate();
		~CMyAllocate();

		/// <summary>
		/// �����ڴ�ռ�
		/// </summary>
		/// <param name="_Size"></param>
		/// <returns></returns>
		void* AllocateSpace(size_t _Size);

		/// <summary>
		/// �ͷ��ڴ�ռ�
		/// </summary>
		/// <param name="_Head"></param>
		void DeleteSpace(void* _Head);

		static size_t m_unNewCount;//����new�Ĵ���
		static size_t m_unMallocCount;//����malloc�Ĵ���

		typedef struct _EMBEDDED_INFO//Ƕ��ʽ�ṹ��
		{
			_EMBEDDED_INFO* ptNext;//Ƕ��ʽ�ṹ��ָ��

		}EMBEDDED_INFO, * PEMBEDDED_INFO;
	private:
		EMBEDDED_INFO* m_ptCanAllocMemory = nullptr;//���Է�����ڴ��ַ
		static size_t m_unMemoryMul;//�����ڴ��Ĵ�СΪ����ı���
	};

	//����������ڴ����
	class CTestMemoryPool
	{
	public:
		CTestMemoryPool();
		~CTestMemoryPool();

		int m_nValue1;
		int m_nValue2;//��֤�����ֽ�������4�ֽ�

		static void* operator new(size_t _Size);
		static void operator delete(void* _Head);
	private:
		static CMyAllocate m_cMyAllocate;
		
	};

	//�����ڴ�غ���
	void Test02();
}