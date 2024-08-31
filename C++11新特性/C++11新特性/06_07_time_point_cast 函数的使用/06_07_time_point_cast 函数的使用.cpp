/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_06_duration_cast 函数的使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.05.20
描  述: 测试 time_point_cast 时间点强制类型转换函数
备  注:
        时间点支持隐式类型转换的条件，时钟需一致，且其内部时间段需满足一下要求：
            1）如果是对时钟周期进行转换：源时钟周期必须能够整除目的时钟周期（比如：小时到分钟）
            2）如果是对时钟周期次数的类型进行转换：低等类型默认可以向高等类型进行转换（比如：int转double）
            3）如果时钟周期和时钟周期次数类型都变了，根据第二点进行推导（也就是看时间周期次数类型）
            4）以上条件都不满足，那么就需要使用 duration_cast 进行显示类型转换

修改记录:

  1.  日期: 2024.05.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include <iostream>
#include <chrono>

using namespace std;

template<typename T>
using MyTimePoint = chrono::time_point<chrono::system_clock, T>;

void Test()
{
    MyTimePoint<chrono::minutes> cMyTimePoint01(chrono::hours(1));

    //时间点显示转换
    MyTimePoint<chrono::hours> cMyTimePoint02(chrono::time_point_cast<chrono::hours>(cMyTimePoint01));
}

int main()
{
    Test();
    return EXIT_SUCCESS;
}

