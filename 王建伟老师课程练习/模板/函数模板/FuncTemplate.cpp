#include <iostream>

#include"FuncTemplate.h"

using namespace std;

//函数模板测试
void FuncTemplate_NameSpace::Test01()
{
    cout << FuncTemplate_NameSpace::Add_01(2, 3) << endl;
    cout << FuncTemplate_NameSpace::Add_01(2.1, 3.2) << endl;

    cout << "非类型模板参数：" << endl;
    cout << FuncTemplate_NameSpace::Add_02<1, 2>() << endl;
    cout << FuncTemplate_NameSpace::Add_03<double, 1, 2>(3.6) << endl;

    putchar('\n');

    //编译器可以进行自动长度推断
    //下述两种调用方式均可以使用
    cout << FuncTemplate_NameSpace::StrCompare<>("ZhangSan", "LiSi") << endl;
    cout << FuncTemplate_NameSpace::StrCompare<9, 5>("ZhangSan", "LiSi") << endl;

}