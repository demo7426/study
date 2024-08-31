/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_01_通过duration创建一个时间段.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.05.12
描  述: 使用C++内部提供的 chrono 命名空间库创建时间段
备  注:
        std::chrono::duration<_Arg01, _Arg02> _Arg01--周期次数，_Arg02--周期大小
        std::ratio<_Molecule, _Denominator> 代表周期大小，_Molecule/_Denominator为周期实际大小

修改记录:

  1.  日期: 2024.05.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include <iostream>
#include <chrono>

using namespace std;

void Test01()
{
    std::chrono::duration<int, std::ratio<3600, 1>> cDuration_Hour01(1);                //创建了 1 个 1小时 的时间段;     等同于std::chrono::hours cHour01;
    std::chrono::duration<double, std::ratio<3600>> cDuration_Hour02(1.5);              //创建了 1.5 个 1小时 的时间段
    std::chrono::hours cHour01;

    std::chrono::duration<int, std::ratio<60, 1>> cDuration_Minutes01(1);               //创建了 1 个 1分钟 的时间段;     等同于std::chrono::minutes cMinutes01;
    std::chrono::minutes cMinutes01;

    std::chrono::duration<int, std::ratio<1, 1>> cDuration_Sec01(1);                    //创建了 1 个 1秒钟 的时间段;     等同于std::chrono::seconds cSec01;
    std::chrono::seconds cSec01;

    std::chrono::duration<int, std::ratio<1, 1000>> cDuration_MilSec01(1);               //创建了 1 个 1毫秒 的时间段;     等同于std::chrono::milliseconds cMilSec01;
    std::chrono::milliseconds cMilSec01;

    std::chrono::duration<int, std::ratio<1, 1000'000>> cDuration_MicSec01(1);           //创建了 1 个 1微秒 的时间段;     等同于std::chrono::microseconds cMicSec01;
    std::chrono::microseconds cMicSec01;

    std::chrono::duration<int, std::ratio<1, 1000'000'000>> cDuration_NanoSec01(1);      //创建了 1 个 1纳秒 的时间段;     等同于std::chrono::nanoseconds cNanoSec01;
    std::chrono::nanoseconds cNanoSec01;


    std::cout << cDuration_Hour01.count() << ", " << cDuration_Hour02.count() << std::endl;
}

int main()
{
    Test01();

    return EXIT_SUCCESS;
}

