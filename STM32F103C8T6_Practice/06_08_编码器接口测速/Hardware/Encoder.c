/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Encoder.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.14
描  述: 编码器测速模块
备  注:  
修改记录: 

  1.  日期: 2024.12.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "Encoder.h"

/// @brief 初始化
/// @param 无
/// @return 无
void Encoder_Init(void)
{
	TIM_TimeBaseInitTypeDef tTIM_TimeBaseInitTypeDef;
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	TIM_ICInitTypeDef tTIM_ICInitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);				
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_IPU;					//设置为上拉输入
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);			//使能定时器2的时钟
	
	tTIM_TimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;		//不分频
	tTIM_TimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;	//设置计数器模式:向上计数
	tTIM_TimeBaseInitTypeDef.TIM_Period = 65536 - 1;				
	tTIM_TimeBaseInitTypeDef.TIM_Prescaler = 1 - 1;					//定时器预分频器
	tTIM_TimeBaseInitTypeDef.TIM_RepetitionCounter = 0;				//重复计数器的值
	
	TIM_TimeBaseInit(TIM3, &tTIM_TimeBaseInitTypeDef);				//设置时基单元
	
	//设置输入捕获单元相关参数
	TIM_ICStructInit(&tTIM_ICInitTypeDef);
	tTIM_ICInitTypeDef.TIM_Channel = TIM_Channel_1;
	tTIM_ICInitTypeDef.TIM_ICFilter = 0xF;							//滤波
	TIM_ICInit(TIM3, &tTIM_ICInitTypeDef);
	
	tTIM_ICInitTypeDef.TIM_Channel = TIM_Channel_2;
	tTIM_ICInitTypeDef.TIM_ICFilter = 0xF;							//滤波
	TIM_ICInit(TIM3, &tTIM_ICInitTypeDef);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_Cmd(TIM3, ENABLE);
}

short Encoder_GetCurCounter(void)
{
	short sTmp = TIM_GetCounter(TIM3);
	
	TIM_SetCounter(TIM3, 0);
	
	return sTmp;
}


