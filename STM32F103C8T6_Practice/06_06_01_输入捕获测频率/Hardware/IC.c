/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	IC.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.13
描  述: 输入捕获频率、占空比模块
备  注:  
修改记录: 

  1.  日期: 2024.12.13
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "IC.h"

void IC_Init(void)
{
	TIM_TimeBaseInitTypeDef tTIM_TimeBaseInitTypeDef;
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	TIM_ICInitTypeDef tTIM_ICInitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);				
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_IPU;					//设置为上拉输入
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_6;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);			//使能定时器2的时钟
	
	TIM_InternalClockConfig(TIM3);									//选择使用内部时钟
	
	tTIM_TimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;		//不分频
	tTIM_TimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;	//设置计数器模式:向上计数
	
	tTIM_TimeBaseInitTypeDef.TIM_Period = 65536 - 1;				
	tTIM_TimeBaseInitTypeDef.TIM_Prescaler = 72 - 1;				//定时器预分频器
	tTIM_TimeBaseInitTypeDef.TIM_RepetitionCounter = 0;				//重复计数器的值
	
	TIM_TimeBaseInit(TIM3, &tTIM_TimeBaseInitTypeDef);				//设置时基单元
	
	//设置输入捕获单元相关参数
	
	tTIM_ICInitTypeDef.TIM_Channel = TIM_Channel_1;
	tTIM_ICInitTypeDef.TIM_ICFilter = 0xF;							//滤波
	tTIM_ICInitTypeDef.TIM_ICPolarity = TIM_ICPolarity_Rising;		//上升沿触发
	tTIM_ICInitTypeDef.TIM_ICPrescaler = TIM_ICPSC_DIV1;			//1分频
	tTIM_ICInitTypeDef.TIM_ICSelection = TIM_ICSelection_DirectTI;	//通道直连
	
	TIM_ICInit(TIM3, &tTIM_ICInitTypeDef);
	
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3, ENABLE);
}

unsigned int IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1(TIM3) + 1);
}
