#include<iostream>

#include "Template_FunWritingAnalysis.h"

using namespace std;
using namespace Template_FunWritingAnalysis_NameSpace;

CAdd::CAdd()
{
	cout << "����CAdd���캯��" << endl;
}

CAdd::CAdd(const CAdd& _Add)
{
	cout << "����CAdd�������캯��" << endl;
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
	cout << CaculateFunc(3, 4, CAdd()) << endl;//����д������������һ����ʱ�Ŀɵ��ö���
}
