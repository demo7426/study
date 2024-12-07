/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	CountSensor.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.07
描  述: 对射式红外传感器模块
备  注:  
修改记录: 

  1.  日期: 2024.12.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "CountSensor.h"

static uint32_t g_unCount = 0;			//对射式红外传感器被触发计数

/// @brief 初始化
/// @param 无
/// @return 无
void CountSensor_Init(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	EXTI_InitTypeDef tEXTI_InitTypeDef;
	NVIC_InitTypeDef tNVIC_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);			//使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			//使能AFIO时钟
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_IPU;					//设置为上拉输入
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_14;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &tGPIO_InitTypeDef);							//初始化GPIO
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);	//配置AFIO的输入
	
	tEXTI_InitTypeDef.EXTI_Line = EXTI_Line14;
	tEXTI_InitTypeDef.EXTI_LineCmd = ENABLE;
	tEXTI_InitTypeDef.EXTI_Mode = EXTI_Mode_Interrupt;
	tEXTI_InitTypeDef.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&tEXTI_InitTypeDef);									//设置EXIT
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	tNVIC_InitTypeDef.NVIC_IRQChannel = EXTI15_10_IRQn;
	tNVIC_InitTypeDef.NVIC_IRQChannelCmd = ENABLE;
	tNVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority = 2;
	tNVIC_InitTypeDef.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&tNVIC_InitTypeDef);									//设置NVIC的中断优先级
}

unsigned int CountSensor_GetCurCount(void)
{
	return g_unCount;
}

void EXTI15_10_IRQHandler(void)										//中断函数
{
	if(EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		g_unCount++;
		
		EXTI_ClearITPendingBit(EXTI_Line14);						//清除对应中断标志位
	}
}
