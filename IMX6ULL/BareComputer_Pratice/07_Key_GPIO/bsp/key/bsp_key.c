/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	bsp_key.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.18
描  述: 实现key按键输入读取功能
备  注:
修改记录:

  1.  日期: 2024.08.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0      

*************************************************/
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "bsp_delay.h"
#include "bsp_gpio.h"

#include "bsp_key.h"

/// @brief 获取按键当前值
/// @param 按键
/// @return 0--按键被按下;1--按键被释放
static inline int GetKeyCurValue(enum Bsp_KeyInit _Key)
{
    uint8_t uchValue = 0;

    Bsp_GPIOGetInput(GPIO1, 18, &uchValue);

    return uchValue;
}

int Bsp_KeyInit(enum Bsp_KeyInit _Key)
{
    switch (_Key)
    {
    case BSP_KEY0:
    {
        BSP_GPIO_CONFIG tBsp_GPIO_Config;

        //设置IO多路复用
        IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);

        //设置GPIO电气属性
        IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xf080);

        //设置GPIO为输出模式
        tBsp_GPIO_Config.Direction = BSP_GPIO_INPUT;
        Bsp_GPIOInit(GPIO1, 18, &tBsp_GPIO_Config);
    }
    break;
    default:
        break;
    }

    return 0;
}


int GetKey_CurStatus(enum Bsp_KeyInit _Key, int* _Status)
{
    switch (_Key)
    {
    case BSP_KEY0:
    {
        //软件消除按键的抖动
        if (GetKeyCurValue(_Key) == 0)     //按键被按下
        {
            Bsp_Delay(10);

            if(GetKeyCurValue(_Key) == 0)
                *_Status = 0;
        }
        else if(GetKeyCurValue(_Key) == 1)
        {
            *_Status = 1;
        }
    }
    break;
    default:
        break;
    }

    return 0;
}


