#pragma once

#include<iostream>
#include<string>

using namespace std;

//类模板
namespace ClassTemplate_NameSpace
{
	/// <summary>
	/// 类型模板参数
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Vector
	{
	public:
		Vector();
		~Vector();

		typedef T* iterator;//迭代器

		Vector& operator=(const Vector&);

		iterator begin();//迭代器的起始位置
		iterator end();//迭代器的起始位置
	};

	template<typename T>
	inline Vector<T>::Vector(){}

	template<typename T>
	inline Vector<T>::~Vector(){}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(const Vector<T>&)
	{
		// TODO: 在此处插入 return 语句
		return *this;
	}
	
	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::begin()//typename 显式的告诉编译器后面接的类元素是一个类型名（如果不写，编译器无法推断）
	{
		return this;
	}

	template<typename T>
	inline T* Vector<T>::end()
	{
		return this;
	}

	//非类型模板参数（类模板中该参数不支持实数、类，只支持正型）
	template<typename T, int _Size = 10>
	class Vector02
	{
	public:
		Vector02();
		~Vector02();

	private:
		T m_array[_Size];
	};

	template<typename T, int _Size>
	Vector02<T, _Size>::Vector02()
	{
		cout << "非类型模板参数：构造函数打印信息：" <<_Size << endl;
	}

	template<typename T, int _Size>
	Vector02<T, _Size>::~Vector02()
	{
	}

	//测试
	void Test01();

}