/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_04_时钟类 steady_clock 的使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.05.20
描  述: 测试C++内部提供的 steady_clock 固定时钟
备  注:

修改记录:

  1.  日期: 2024.05.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <chrono>

using namespace std;

void Test(void)
{
    //获取当前固定时钟时间点对象
    chrono::steady_clock::time_point cTimePoint01 = chrono::steady_clock::now();

    int nValue = 0;
    for (size_t i = 0; i < 20'000; i++)
    {
        nValue++;
    }

    chrono::steady_clock::time_point cTimePoint02 = chrono::steady_clock::now();

    auto cTimeDuration = cTimePoint02 - cTimePoint01;
    std::cout << "用时 " << cTimeDuration.count() << " ns" << std::endl;
}

int main()
{
    Test();
    return EXIT_SUCCESS;
}

