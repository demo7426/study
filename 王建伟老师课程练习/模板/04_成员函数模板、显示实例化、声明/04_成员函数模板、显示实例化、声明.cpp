#include"Template_ClassMemberFuncTempalte.h"

#include <iostream>

using namespace Template_ClassMemberFuncTempalte_NameSpace;
using namespace std;
 
//显示实例化定义模板，减少编译时期生成.o文件的代码量（只需要写入一次定义即可）
//缺点:显示实例化定义类模板会生成所有的成员函数类型、属性
template CStudent<int>;
template int Template_ClassMemberFuncTempalte_NameSpace::Calculator_Add(const int& _X, const int& _Y);

int main()
{
    CStudent<int> cStudent;

    std::cout << "Hello World!\n";
    return EXIT_SUCCESS;
}

