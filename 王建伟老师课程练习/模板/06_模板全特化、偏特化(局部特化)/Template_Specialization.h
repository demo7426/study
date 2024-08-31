#pragma once

#include<iostream>

using namespace std;

/// <summary>
/// 模板特化目录:
///	(1)类模板特化
///		(1.1)类模板全特化
///			a)常规全特化
///			b)特化成员函数而不是类模板
///		(1.2)类模板偏特化（局部特化）
///			a)模板参数数量
///			b)模板参数范围
/// (2)函数模板特化
///		(2.1)函数模板全特化
///		(2.2)函数模板偏特化(编译可以通过，但是功能不存在)
/// (3)模板特化版本放置位置建议
/// </summary>
namespace Template_Specialization_NameSpace
{
	template<typename T, typename U,typename W>
	struct CCaculator
	{
		CCaculator()
		{
			cout << "CCaculator类模板泛型：构造函数！" << endl;
		}

		T Add(U _X, W _Y)
		{
			cout << "CCaculator类模板泛型：Add()函数！" << endl;
			return _X + _Y;
		}
	};


	//类模板常规全特化
	template<>
	struct CCaculator<double, int, int>
	{
		CCaculator()
		{
			cout << "CCaculator类模板全特化：构造函数！" << endl;
		}

		template<typename T, typename U, typename W>
		T Add(U _X, W _Y)
		{
			cout << "CCaculator类模板全特化：Add()函数！" << endl;
			return _X + _Y;
		}
	};

	//类模板全特化，特化成员函数而不是类模板
	template<>
	int CCaculator<int, int, int>::Add(int _X, int _Y)
	{
		cout << "CCaculator类模板全特化，特化成员函数：Add()函数！" << endl;
		return _X + _Y;
	}

	//类模板偏特化、模板参数数量
	template<typename U>
	struct CCaculator<string, U, string>
	{
		CCaculator()
		{
			cout << "CCaculator类模板偏特化、模板参数数量：构造函数！" << endl;
		}

		string Add(U _X, string _Y)
		{
			cout << "CCaculator类模板偏特化、模板参数数量：Add()函数！" << endl;
			return _X + _Y;
		}
	};

	//类模板偏特化、模板参数范围
	template<>
	struct CCaculator<int, int&, int&>
	{
		template<typename T, typename U, typename W>
		T Add(U _X, W _Y)
		{
			cout << "CCaculator类模板偏特化、模板参数范围：Add()函数！" << endl;
			return _X + _Y;
		}
	};

	//函数模板
	template<typename T, typename U, typename W >
	T Mul(U _X, W _Y)
	{
		cout << "函数模板泛型：Mul()函数！" << endl;
		return _X * _Y;
	}

	//函数模板全特化
	template<>
	double Mul(double _X, int _Y)
	{
		cout << "函数模板全特化：Mul()函数！" << endl;
		return _X * _Y;
	}

	//函数模板没有偏特化功能，编译可以通过，但是功能不存在
	template<typename U>
	int Mul(U _X, double _Y)
	{
		cout << "函数模板偏特化：Mul()函数！" << endl;
		return _X * _Y;
	}

	//测试函数
	void Test01();
}