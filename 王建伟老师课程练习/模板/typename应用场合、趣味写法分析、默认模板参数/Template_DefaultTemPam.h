#pragma once

/// <summary>
/// 默认模板参数
/// </summary>
namespace Template_DefaultTemPam_NameSpace
{
	/// <summary>
	/// 类默认模板参数
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T, int _Size = 20, int _Capacity = 50>
	class CList
	{
	public:
		CList();
		~CList();

		int operator ()(int _X, int _Y)const
		{
			return _X + _Y;
		}
	private:

	};

	template<typename T, int _Size, int _Capacity>
	CList<T, _Size, _Capacity>::CList()
	{
	}

	template<typename T, int _Size, int _Capacity>
	CList<T, _Size, _Capacity>::~CList()
	{
	}

	typedef int FuncTypename(int _X, int _Y);

	/// <summary>
	/// 求和函数
	/// </summary>
	/// <param name="_X"></param>
	/// <param name="_Y"></param>
	/// <returns></returns>
	int Add(int _X, int _Y);

	//函数默认模板参数
	template<typename T01, typename T02 = FuncTypename>
	T01 CallFunc01(T01 _X, T01 _Y, T02 _Func = Add)	{}

	//函数默认模板参数
	template<typename T01, typename T02 = CList<int>>
	T01 CallFunc02(T01 _X, T01 _Y, T02 _Func = CList<int>()){}
}