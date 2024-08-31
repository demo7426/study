#include<iostream>

#include "Template_FunWritingAnalysis.h"

using namespace std;
using namespace Template_FunWritingAnalysis_NameSpace;

CAdd::CAdd()
{
	cout << "调用CAdd构造函数" << endl;
}

CAdd::CAdd(const CAdd& _Add)
{
	cout << "调用CAdd拷贝构造函数" << endl;
}

CAdd::~CAdd()
{
}

int Template_FunWritingAnalysis_NameSpace::Add(int _X, int _Y)
{
	return _X + _Y;
}

template<typename T01, typename T02>
int Template_FunWritingAnalysis_NameSpace::CaculateFunc(T01 _X, T01 _Y, T02 _Func)
{
	return _Func(_X, _Y);
}

void Template_FunWritingAnalysis_NameSpace::Test01()
{
	cout << CaculateFunc(2, 3, Add) << endl;

	putchar('\n');
	CAdd cAdd;
	cout << CaculateFunc(3, 4, cAdd) << endl;

	putchar('\n');
	cout << CaculateFunc(3, 4, CAdd()) << endl;//特殊写法，可以生成一个临时的可调用对象
}
