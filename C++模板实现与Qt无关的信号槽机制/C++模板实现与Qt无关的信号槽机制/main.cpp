/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.25
描  述: 实现 C++模板实现与Qt无关的信号槽机制 测试
备  注:	官方依赖库：          https://sigslot.sourceforge.net/
        国内修改后的依赖库：  https://www.cnblogs.com/pandamohist/p/13717612.html     //源官方依赖出现了编译错误的问题，故使用国内修改后版本
        国内视频讲解：         https://www.bilibili.com/video/BV1YhidBKEVK?t=599.0
修改记录:

  1.  日期: 2025.01.25
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <iostream>
#include <thread>
#include <chrono>

#include "sigslot.h"

class CWindow
{
public:
	CWindow() = default;
	~CWindow() = default;
    
    sigslot::signal0<> m_cSig_LeftBtnClick;             //左键点击信号 
    sigslot::signal1 <int> m_cSig_RightBtnClick;        //右键点击信号 

};

class CWindowHandler : public sigslot::has_slots<>
{
public:
    void LeftBtnClick()
    {
        std::cout << "左键点击" << std::endl;
    }

    void RightBtnClick(int _Arg)
    {
        std::cout << "右键点击，" << _Arg << std::endl;
    }
};


int main()
{
    int32_t i = 0;

    CWindow cWin;
    CWindowHandler cWinHandler;

    cWin.m_cSig_LeftBtnClick.connect(&cWinHandler, &CWindowHandler::LeftBtnClick);
    cWin.m_cSig_RightBtnClick.connect(&cWinHandler, &CWindowHandler::RightBtnClick);

    while (1)
    {
        //发出信号
        cWin.m_cSig_LeftBtnClick();
        cWin.m_cSig_RightBtnClick(++i);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}

