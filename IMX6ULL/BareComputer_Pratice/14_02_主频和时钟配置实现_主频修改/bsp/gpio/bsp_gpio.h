/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	bsp_gpio.h
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

#ifndef __BSP_GPIO_H_
#define __BSP_GPIO_H_

#include "cc.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"


/// @brief 设置GPIO为输入还是输出
typedef enum _BSP_GPIO_DIRECTION
{
    BSP_GPIO_INPUT = 1,                 //输入
    BSP_GPIO_OUTPUT                     //输出
}BSP_GPIO_DIRECTION;

typedef struct _BSP_GPIO_CONFIG
{
    BSP_GPIO_DIRECTION Direction;       //输入还是输出
    uint8_t OutputLogic;                //输出的默认值
}BSP_GPIO_CONFIG, *PBSP_GPIO_CONFIG;

/// @brief 初始化GPIO，若是设置为输出，则设置其默认输出电平
/// @param _pGPIO GPIO
/// @param _Pin pin脚
/// @param _pConfig 初始化参数
/// @return -2--函数执行失败;-1--输入参数错误;0--函数执行成功
int Bsp_GPIOInit(GPIO_Type* _pGPIO, const uint32_t _Pin, const PBSP_GPIO_CONFIG _pConfig);

/// @brief 设置GPIO输出电平
/// @param _pGPIO GPIO
/// @param _Pin pin脚
/// @param _Value 0--低电平，高电平
/// @return -2--函数执行失败;-1--输入参数错误;0--函数执行成功
int Bsp_GPIOSetOutput(GPIO_Type* _pGPIO, const uint32_t _Pin, const uint8_t _Value);

/// @brief 获取GPIO输入电平
/// @param _pGPIO GPIO
/// @param _Pin pin脚
/// @param _pValue 当前电平值
/// @return -2--函数执行失败;-1--输入参数错误;0--函数执行成功
int Bsp_GPIOGetInput(GPIO_Type* _pGPIO, const uint32_t _Pin, uint8_t* _pValue);

#endif // !__BSP_GPIO_H_


