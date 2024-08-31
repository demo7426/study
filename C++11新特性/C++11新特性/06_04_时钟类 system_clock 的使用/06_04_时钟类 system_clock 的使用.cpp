/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_04_时钟类 system_clock 的使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.05.20
描  述: 测试C++内部提供的 system_clock 系统时钟
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
    //创建一个时间点对象
    chrono::system_clock::time_point cTimePiont01;

    chrono::hours cHours(10 * 24);
    chrono::system_clock::time_point cTimePiont02 = cTimePiont01 + cHours;

    //获取当前的时间点
    chrono::system_clock::time_point cTimePiont_Now = chrono::system_clock::now();
    
    //时间点->以1970/01/01开始的时间段(单位秒)
    time_t llAllSec = chrono::system_clock::to_time_t(cTimePiont_Now);
    std::cout << "当前时间为：" << ctime(&llAllSec) << std::endl;

    //以1970/01/01开始的时间段->时间点
    chrono::system_clock::time_point cTiemPoint02 = chrono::system_clock::from_time_t(llAllSec);
}

int main()
{
    Test();
    return EXIT_SUCCESS;
}

