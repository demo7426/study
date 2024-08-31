#include <iostream>
#include"FuncTemplate.h"
#include"../类模板/ClassTemplate.h"
#include"../类模板/ClassTemplate.cpp"
#include"../typename应用场合、趣味写法分析、默认模板参数/Template_FunWritingAnalysis.h"
#include"../typename应用场合、趣味写法分析、默认模板参数/Template_FunWritingAnalysis.cpp"
#include"../05_using定义模板别名,显式指定模板参数/Template_UsingDefTemplateAlias.h"
#include"../05_using定义模板别名,显式指定模板参数/Template_UsingDefTemplateAlias.cpp"
#include"../06_模板全特化、偏特化(局部特化)/Template_Specialization.h"
#include"../06_模板全特化、偏特化(局部特化)/Template_Specialization.cpp"
#include"../07_可变参模板/Template_VariadicPam.h"
#include"../07_可变参模板/Template_VariadicPam.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    puts("01_函数模板测试：");
    FuncTemplate_NameSpace::Test01();

    puts("\n02_类模板测试：");
    ClassTemplate_NameSpace::Test01();
    
    puts("\n03_趣味写法分析、默认模板参数测试：");
    Template_FunWritingAnalysis_NameSpace::Test01();

    puts("\n05_using定义模板别名,显示指定模板参数：");
    Template_UsingDefTemplateAlias_NameSpace::Test01();

    puts("\n06_模板全特化、偏特化(局部特化)：");
    Template_Specialization_NameSpace::Test01();

    puts("\n06_可变参模板：");
    Template_VariadicPam_NameSpace::Test01();

    return EXIT_SUCCESS;
}