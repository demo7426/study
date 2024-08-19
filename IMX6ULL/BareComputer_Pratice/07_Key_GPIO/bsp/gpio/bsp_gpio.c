/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	bsp_gpio.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.19
描  述: 实现对gpio的控制
备  注:
修改记录:

  1.  日期: 2024.08.19
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0      

*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "bsp_gpio.h"

int Bsp_GPIOInit(GPIO_Type* _pGPIO, const uint32_t _Pin, const PBSP_GPIO_CONFIG _pConfig)
{
    if(_pGPIO == NULL)
        return -1;

    switch (_pConfig->Direction)
    {
    case BSP_GPIO_INPUT:                    
        _pGPIO->GDIR &= ~(1 << _Pin);                                       //设置为输入
        break;
    case BSP_GPIO_OUTPUT:                    
        _pGPIO->GDIR |= (1 << _Pin);                                        //设置为输出
        Bsp_GPIOSetOutput(_pGPIO, _Pin, _pConfig->OutputLogic);             //设置默认输出电平
        break;
    default:
        break;
    }

    return 0;
}

int Bsp_GPIOSetOutput(GPIO_Type* _pGPIO, const uint32_t _Pin, const uint8_t _Value)
{
    if(_pGPIO == NULL)
        return -1;

    switch (_Value)
    {
    case 0:
        GPIO5->DR |= (1 << _Pin);
        break;
    case 1:
        GPIO5->DR &= ~(1 << _Pin);
        break;
    default:
        return -1;
        break;
    }

    return 0;
}

int Bsp_GPIOGetInput(GPIO_Type* _pGPIO, const uint32_t _Pin, uint8_t* _pValue)
{
    if(_pGPIO == NULL || _pValue == NULL)
        return -1;

    *_pValue = ((_pGPIO->DR) >> _Pin) & 0x1;
    return 0;
}
