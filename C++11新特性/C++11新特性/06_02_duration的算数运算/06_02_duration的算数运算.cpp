/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_02_duration的算数运算.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.05.12
描  述: 测试C++内部提供的 chrono::duration 类重载运算符
备  注:
        std::chrono::duration<_Arg01, std::ratio<_Molecule, _Denominator>> 
        在进行计算时，会先将 _Molecule 转换为最大公约数，_Denominator 转换为最大公倍数在进行计算

修改记录:

  1.  日期: 2024.05.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include <iostream>
#include <chrono>

void Test01()
{
    std::chrono::minutes cMinutes01(10);
    std::chrono::minutes cMinutes02(8);

    cMinutes01++;
    cMinutes02--;

    std::cout << "周期数 = " << (cMinutes01 - cMinutes02).count() << std::endl;

    std::chrono::duration<int, std::ratio<60, 1>> Minutes03(10);
    std::chrono::duration<int, std::ratio<60, 1>> Minutes04(8);

    std::cout << "周期数 = " << (Minutes03 - Minutes04).count() << std::endl;

    std::chrono::duration<int, std::ratio<40, 3>> Minutes05(8);

    auto MinutesSum = Minutes03 - Minutes05;

    std::cout << "周期数 = " << MinutesSum.count() << std::endl;
}

int main()
{
    Test01();

    return EXIT_SUCCESS;
}


