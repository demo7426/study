#pragma once

#include<iostream>
#include<string>

using namespace std;

//��ģ��
namespace ClassTemplate_NameSpace
{
	/// <summary>
	/// ����ģ�����
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Vector
	{
	public:
		Vector();
		~Vector();

		typedef T* iterator;//������

		Vector& operator=(const Vector&);

		iterator begin();//����������ʼλ��
		iterator end();//����������ʼλ��
	};

	template<typename T>
	inline Vector<T>::Vector(){}

	template<typename T>
	inline Vector<T>::~Vector(){}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(const Vector<T>&)
	{
		// TODO: �ڴ˴����� return ���
		return *this;
	}
	
	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::begin()//typename ��ʽ�ĸ��߱���������ӵ���Ԫ����һ���������������д���������޷��ƶϣ�
	{
		return this;
	}

	template<typename T>
	inline T* Vector<T>::end()
	{
		return this;
	}

	//������ģ���������ģ���иò�����֧��ʵ�����ֻ֧࣬�����ͣ�
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
		cout << "������ģ����������캯����ӡ��Ϣ��" <<_Size << endl;
	}

	template<typename T, int _Size>
	Vector02<T, _Size>::~Vector02()
	{
	}

	//����
	void Test01();

}