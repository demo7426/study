/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	LightSensor.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.06
描  述: 光敏传感器模块
备  注:  
修改记录: 

  1.  日期: 2024.12.06
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "LightSensor.h"

void LightSensor_Init(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//使能GPIO时钟
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_IPU;				//设置为上拉输入
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_13;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &tGPIO_InitTypeDef);						//初始化GPIO
}

unsigned char LightSensor_GetDO(void)
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}

