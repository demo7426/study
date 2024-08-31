/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_10_CPP中多线程的创建和使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.05.24
描  述: 测试 C++11标准 提供的多线程的创建
备  注:
修改记录:

  1.  日期: 2024.05.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include <iostream>
#include <thread>

using namespace std;

void CallBackFunc(std::string _Name, int _Age)
{
    std::cout << "This thread id is " << this_thread::get_id() << " _Name: " << _Name << " _Age" << _Age << std::endl;
}

int Test(void)
{
    thread cTh01;

    thread cTh02(CallBackFunc, "Cristiano", 39);

    thread cTh03([=](std::string _Name, int _Age) {
        std::cout << "This thread id is "<< this_thread::get_id() << " _Name: " << _Name << " _Age" << _Age << std::endl;
        }, "Robert Lewandowski", 36);

    thread cTh04(std::move(cTh03));         //移动构造

    cTh02.join();
    cTh04.join();

    return EXIT_SUCCESS;
}

int main()
{
    Test();

    return EXIT_SUCCESS;
}

