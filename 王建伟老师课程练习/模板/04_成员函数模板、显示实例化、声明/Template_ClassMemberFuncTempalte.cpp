#include<string>

#include"Template_ClassMemberFuncTempalte.h"

using namespace Template_ClassMemberFuncTempalte_NameSpace;

//��ʾʵ��������ģ�壬���ٱ���ʱ������.o�ļ��Ĵ�������ֻ��Ҫ��Ҫʹ�ø�ģ���Դ�ļ�д���������ɣ�
extern template CStudent<int>;
extern template int Template_ClassMemberFuncTempalte_NameSpace::Calculator_Add(const int& _X, const int& _Y);

static void Func01()
{
	CStudent<int> cStudent;
	std::string strName = cStudent.GetName<std::string>(3);

}