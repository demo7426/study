/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_13_CPP中多线程的创建和使用_05.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.06.04
描  述: 测试 C++11标准 thread命名空间提供的 joinable、handware_concurrency 函数
备  注:
修改记录:

  1.  日期: 2024.06.04
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void CallBack_Func01(string _Name, unsigned int _Age)
{
    std::cout << _Name << "'s age is " << _Age << std::endl;
}

//joinable 可用于判断父子线程是否处于关联状态
void Test01()
{
    thread cTh01;
    std::cout << "cTh01 joinable is " << cTh01.joinable() << std::endl;

    thread cTh02(CallBack_Func01, "Cristiano", 39);
    std::cout << "cTh02 joinable is " << cTh02.joinable() << std::endl;
    cTh02.join();
    std::cout << "cTh02 joinable is " << cTh02.joinable() << std::endl;


    thread cTh03(CallBack_Func01, "Neymar", 32);
    std::cout << "cTh03 joinable is " << cTh03.joinable() << "\n";

    this_thread::sleep_for(std::chrono::duration<int>());
    cTh03.detach();
    std::cout << "cTh03 joinable is " << cTh03.joinable() << std::endl;
}

//handware_concurrency 用于获取cpu核心数量
void Test02()
{
    std::cout << "Current cpu num is " << std::thread::hardware_concurrency() << "\n";
}


int main()
{
    Test01();
    Test02();

    return EXIT_SUCCESS;
}

