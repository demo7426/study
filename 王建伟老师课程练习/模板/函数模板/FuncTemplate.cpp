#include <iostream>

#include"FuncTemplate.h"

using namespace std;

//����ģ�����
void FuncTemplate_NameSpace::Test01()
{
    cout << FuncTemplate_NameSpace::Add_01(2, 3) << endl;
    cout << FuncTemplate_NameSpace::Add_01(2.1, 3.2) << endl;

    cout << "������ģ�������" << endl;
    cout << FuncTemplate_NameSpace::Add_02<1, 2>() << endl;
    cout << FuncTemplate_NameSpace::Add_03<double, 1, 2>(3.6) << endl;

    putchar('\n');

    //���������Խ����Զ������ƶ�
    //�������ֵ��÷�ʽ������ʹ��
    cout << FuncTemplate_NameSpace::StrCompare<>("ZhangSan", "LiSi") << endl;
    cout << FuncTemplate_NameSpace::StrCompare<9, 5>("ZhangSan", "LiSi") << endl;

}