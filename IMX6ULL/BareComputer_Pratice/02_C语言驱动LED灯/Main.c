/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V1.1.0     新建日期: 2024.05.24
描  述: 入口函数文件
备  注:
修改记录:

  1.  日期: 2024.05.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0
  2.  日期: 2024.08.04
      作者: 钱锐
      内容:
          1) 使用C语言实现LED闪烁；
      版本:V1.1.0      

*************************************************/

#include "Led.h"

/// @brief 初始化外设时钟
void InitClock(void)
{
    CCM_CCGR0 = 0xffffffff;
    CCM_CCGR1 = 0xffffffff;
    CCM_CCGR2 = 0xffffffff;
    CCM_CCGR3 = 0xffffffff;
    CCM_CCGR4 = 0xffffffff;
    CCM_CCGR5 = 0xffffffff;
    CCM_CCGR6 = 0xffffffff;
}

/// @brief 初始化GPIO1_IO03参数
void InitGPIO1_IO03(void)
{
    //设置GPIO1_IO03复用为GPTO
    SW_MUX_GPIO1_IO03 = 0x5;

    //设置GPIO电气属性
    SW_PAD_GPIO1_IO03 = 0x10b0;

    //设置GPIO为输出模式
    GPIO1_GRIR = 0x8;
}

/// @brief 延时函数
/// @param _Millsecond--延时时间:单位为ms
void UsrDelay(volatile unsigned int _Millsecond)
{
    if(_Millsecond == 0)            
        return;

    int nFreq = 0x7ff;              //根据cpu主频计算出的延时参数
    while (_Millsecond--)
    {
        while(nFreq--){};
        nFreq = 0x7ff;
    }
}

int main(int argc, char* argv[])
{
    InitClock();
    InitGPIO1_IO03();

    while (1)
    {
        GPIO1_DR &= ~(1<<3);       //led灯亮
        UsrDelay(1000);

        GPIO1_DR |= (1<<3);       //led灯灭
        UsrDelay(1000);
    }
    
    return 0;
}

