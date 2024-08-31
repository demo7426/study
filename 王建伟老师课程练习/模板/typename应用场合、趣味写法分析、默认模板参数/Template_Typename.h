#pragma once

/// <summary>
/// typename有两种用法
/// 1、模板类型名;	2、typename 显式的告诉编译器后面接的类元素是一个类型名（如果不写，编译器无法推断）
/// </summary>
namespace Template_Typename_NameSpace
{
	/// <summary>
	/// 自制deque容器
	/// </summary>
	/// <typeparam name="T">容器内元素类型</typeparam>
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
	typename CDeque<T>::iterator CDeque<T>::begin()//typename 显式的告诉编译器后面接的类元素是一个类型名（如果不写，编译器无法推断）
	{
	}
}