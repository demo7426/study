/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_14_类的成员函数做为子线程的任务函数.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.06.04
描  述: 测试 C++11标准 向 thread 线程传递类的成员函数 
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
#include <functional>

using namespace std;

class CLog
{
public:
    CLog() = default;
    ~CLog() = default;

    static void ShowMsg(string _Msg)
    {
        std::cout << "ShowMsg: msg: " << _Msg << std::endl;
    }

    void ShowTips(string _Tips)
    {
        std::cout << "ShowMsg: tips: " << _Tips << std::endl;
    }

private:

};

void Test01()
{
    CLog cLog;

    //测试类的静态函数

    thread cTh01(&CLog::ShowMsg, "Cristiano is the best fotball palyer.");
    cTh01.join();

    //测试类的非静态函数

    thread cTh02(&CLog::ShowTips, cLog, "It will rain tomorrow 02.");
    cTh02.join();

    thread cTh03(&CLog::ShowTips, &cLog, "It will rain tomorrow 03.");
    cTh03.join();

    thread cTh04(bind(&CLog::ShowTips, cLog, "It will rain tomorrow 04."));
    cTh04.join();

    thread cTh05(bind(&CLog::ShowTips, &cLog, "It will rain tomorrow 05."));
    cTh05.join();
}

int main()
{
    Test01();

    return EXIT_SUCCESS;
}

