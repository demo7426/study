#pragma once

#include<iostream>
#include<map>
#include <string>

using namespace std;

/// <summary>
/// using定义模板别名
/// </summary>
namespace Template_UsingDefTemplateAlias_NameSpace
{
	//实现自定义容器取别名
	
	//C++98实现:
	template<typename T>
	struct _MapStr_T
	{
		typedef map<string, T> mapStr_T;
	};
	
	//C++11实现:
	template<typename T01, typename T02>
	using mapT01_T02 = map<T01, T02>;

	//函数指针取别名
	typedef int (*FuncPtr01)(double, double);

	//函数指针取别名
	template<typename T01, typename T02, typename T03>
	using FuncPtr02 = T01(*)(T02, T03);

	//测试函数
	void Test01();

}