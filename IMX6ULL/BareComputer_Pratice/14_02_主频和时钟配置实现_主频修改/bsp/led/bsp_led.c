/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	bsp_led.c
作  者:	钱锐      版本: V1.1.0     新建日期: 2024.08.11
描  述: 实现bsp led灯文件
备  注:
修改记录:

  1.  日期: 2024.08.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0      

*************************************************/\

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "bsp_led.h"

int Bsp_LedInit(void)
{
    //设置GPIO1_IO03复用为GPTO
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);

    //设置GPIO电气属性
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10b0);

    //设置GPIO为输出模式
    GPIO1->GDIR = 0x8;
    return 0;
}

int Bsp_LedOn(void)
{
    GPIO1->DR &= ~(1<<3);       //led灯亮
    return 0;
}

int Bsp_LedOff(void)
{
    GPIO1->DR |= (1<<3);       //led灯灭
    return 0;
}

int Bsp_LedSwitchStatus(const int _Status)
{
    switch (_Status)
    {
    case 0:
        GPIO1->DR |= (1<<3);       //led灯灭
        break;
    case 1:
        GPIO1->DR &= ~(1<<3);       //led灯亮
        break;
    default:
        break;
    }

    return 0;
}

