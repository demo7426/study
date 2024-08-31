#include<string>

#include"Template_ClassMemberFuncTempalte.h"

using namespace Template_ClassMemberFuncTempalte_NameSpace;

//显示实例化声明模板，减少编译时期生成.o文件的代码量（只需要在要使用该模板的源文件写入声明即可）
extern template CStudent<int>;
extern template int Template_ClassMemberFuncTempalte_NameSpace::Calculator_Add(const int& _X, const int& _Y);

static void Func01()
{
	CStudent<int> cStudent;
	std::string strName = cStudent.GetName<std::string>(3);

}