/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	LED.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.06
描  述: LED灯显示控制
备  注:  
修改记录: 

  1.  日期: 2024.12.06
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "LED.h"

void LED_Init(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//使能GPIO时钟
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;				//设置为推挽输出
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);						//初始化GPIO
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1);							//拉高输出电平，使LED灯熄灭
	GPIO_SetBits(GPIOA, GPIO_Pin_2);							//拉高输出电平，使LED灯熄灭
}

void LED_On_01(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void LED_Off_01(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

void LED_Turn_01(void)
{
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}

void LED_On_02(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

void LED_Off_02(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void LED_Turn_02(void)
{
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
}
