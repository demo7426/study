#pragma once

/// <summary>
/// typename�������÷�
/// 1��ģ��������;	2��typename ��ʽ�ĸ��߱���������ӵ���Ԫ����һ���������������д���������޷��ƶϣ�
/// </summary>
namespace Template_Typename_NameSpace
{
	/// <summary>
	/// ����deque����
	/// </summary>
	/// <typeparam name="T">������Ԫ������</typeparam>
	template<typename T>
	class CDeque
	{
	public:
		typedef T* iterator;

		CDeque();
		~CDeque();

	private:

		iterator begin();
		iterator end() {};
	};

	template<typename T>
	CDeque<T>::CDeque()
	{
	}

	template<typename T>
	CDeque<T>::~CDeque()
	{
	}


	template<typename T>
	typename CDeque<T>::iterator CDeque<T>::begin()//typename ��ʽ�ĸ��߱���������ӵ���Ԫ����һ���������������д���������޷��ƶϣ�
	{
	}
}