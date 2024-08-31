#pragma once

#include<iostream>
#include<map>
#include <string>

using namespace std;

/// <summary>
/// using����ģ�����
/// </summary>
namespace Template_UsingDefTemplateAlias_NameSpace
{
	//ʵ���Զ�������ȡ����
	
	//C++98ʵ��:
	template<typename T>
	struct _MapStr_T
	{
		typedef map<string, T> mapStr_T;
	};
	
	//C++11ʵ��:
	template<typename T01, typename T02>
	using mapT01_T02 = map<T01, T02>;

	//����ָ��ȡ����
	typedef int (*FuncPtr01)(double, double);

	//����ָ��ȡ����
	template<typename T01, typename T02, typename T03>
	using FuncPtr02 = T01(*)(T02, T03);

	//���Ժ���
	void Test01();

}