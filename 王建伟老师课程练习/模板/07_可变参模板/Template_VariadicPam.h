#pragma once

#include<iostream>

using namespace std;

/// <summary>
/// �ɱ����ģ��
/// </summary>
namespace Template_VariadicPam_NameSpace
{
	

	template<typename T, typename...U>
	void Func(const T& _FirstArg, const U&..._OtherArg);

	void Func();

	/// <summary>
	/// ���Ժ���
	/// </summary>
	void Test01();
}