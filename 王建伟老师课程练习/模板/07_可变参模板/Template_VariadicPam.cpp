#include "Template_VariadicPam.h"

using namespace Template_VariadicPam_NameSpace;

template<typename T, typename...U>
void Template_VariadicPam_NameSpace::Func(const T& _FirstArg, const U&..._OtherArg)
{
	cout << _FirstArg << endl;
	Func(_OtherArg...);
}

void Template_VariadicPam_NameSpace::Func()
{
	cout << "���ò����������ֹ����" << endl;
	
}

void Template_VariadicPam_NameSpace::Test01()
{
	Func(1, 2.1, "MeiXi");
}
