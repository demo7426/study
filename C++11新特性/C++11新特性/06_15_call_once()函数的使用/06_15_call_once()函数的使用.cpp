/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_15_call_once()函数的使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.06.12
描  述: 测试 C++11标准 call_once 函数（该函数可以保证在多线程调用时，只会被成功调用一次）
备  注: call_once 函数的第一个参数必须是所有线程均可以访问到的，用该参数保证 call_once 函数只会被调用一次
修改记录:

  1.  日期: 2024.06.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::once_flag g_tOnceFlag;         //保证 call_once 函数只会被调用一次

void Called_Once(string _Name, int _Age)
{
    std::cout << "Called_Once: Name: " << _Name << "Age: " << _Age << '\n';
}

void CalledFunc01(string _Name, int _Age)
{
    call_once(g_tOnceFlag, Called_Once, "SangBa", 20);
    std::cout << "CalledFunc01: Name: " << _Name << "Age: " << _Age << '\n';
}

int Test01()
{
    std::thread cTh01(CalledFunc01, "Critiano01", 39);
    std::thread cTh02(CalledFunc01, "Critiano02", 40);
    std::thread cTh03(CalledFunc01, "Critiano03", 41);

    cTh01.join();
    cTh02.join();
    cTh03.join();

    return EXIT_SUCCESS;
}

int main()
{
    Test01();

    return EXIT_SUCCESS;
}

