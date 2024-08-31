#pragma once

#include<iostream>

using namespace std;

/// <summary>
/// 可变参数模板
/// </summary>
namespace Template_VariadicPam_NameSpace
{
	

	template<typename T, typename...U>
	void Func(const T& _FirstArg, const U&..._OtherArg);

	void Func();

	/// <summary>
	/// 测试函数
	/// </summary>
	void Test01();
}