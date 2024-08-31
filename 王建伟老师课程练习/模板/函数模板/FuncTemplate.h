#pragma once

//ģ��Ķ�����Է���ͷ�ļ���������ֶ��ض�������
namespace FuncTemplate_NameSpace
{
	/// <summary>
	/// ��ͨ����ģ���ʹ��
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="_X"></param>
	/// <param name="_Y"></param>
	/// <returns></returns>
	template<typename T>
	T Add_01(T _X, T _Y)
	{
		return _X + _Y;
	}

	/// <summary>
	/// ������ģ�������ʹ��
	/// </summary>
	/// <returns></returns>
	template<int _X, int _Y>
	int Add_02()
	{
		return _X + _Y;
	}

	/// <summary>
	/// ������ģ�������ʹ��
	/// </summary>
	/// <returns></returns>
	template<typename T, int _X, int _Y>
	T Add_03(T _Z)
	{
		return _X + _Y + _Z;
	}

	/// <summary>
	/// ������ģ�������ʹ��
	/// </summary>
	/// <param name="_Array1"></param>
	/// <param name="_Array2"></param>
	/// <returns></returns>
	template<unsigned int _Length1, unsigned int _Length2>
	int StrCompare(const char (&_Array1)[_Length1], const char(&_Array2)[_Length2])
	{
		return strcmp(_Array1, _Array2);
	}

	void Test01();
}
