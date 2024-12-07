/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Timer.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.07
描  述: 定时器模块
备  注:  
修改记录: 

  1.  日期: 2024.12.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "Timer.h"

void Timer_Init(void)
{
	TIM_TimeBaseInitTypeDef tTIM_TimeBaseInitTypeDef;
	NVIC_InitTypeDef tNVIC_InitTypeDef;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//使能定时器2的时钟
	
	TIM_InternalClockConfig(TIM2);									//选择
	
	tTIM_TimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;		//不分频
	tTIM_TimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;	//设置计数器模式:向上计数
	
	//定时器重装值（定时频率=72MHz/(PSC+1)/(ARR+1)）（定时频率=72MHz/(9999+1)/(7199+1)）
	tTIM_TimeBaseInitTypeDef.TIM_Period = 10000 - 1;				
	tTIM_TimeBaseInitTypeDef.TIM_Prescaler = 7200 - 1;				//定时器预分频器
	tTIM_TimeBaseInitTypeDef.TIM_RepetitionCounter = 0;				//重复计数器的值
	
	TIM_TimeBaseInit(TIM2, &tTIM_TimeBaseInitTypeDef);				//设置时基单元
	
	//清除上一步设置时基单元时，TIMx->EGR = TIM_PSCReloadMode_Immediate; 启动的更新标志位
	//保证定时器从最开始不会被触发
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);							
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);						//中断输出控制
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);					//设置NVIC的中断优先级分组
	
	tNVIC_InitTypeDef.NVIC_IRQChannel = TIM2_IRQn;					//中断通道
	tNVIC_InitTypeDef.NVIC_IRQChannelCmd = ENABLE;					
	tNVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority = 2;		//抢占优先级
	tNVIC_InitTypeDef.NVIC_IRQChannelSubPriority = 1;				//响应优先级
	
	NVIC_Init(&tNVIC_InitTypeDef);									//设置NVIC的中断优先级
	
	TIM_Cmd(TIM2, ENABLE);											//启动定时器
}

/*
//定时器2中断模板
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);						//清除对应中断标志位
	}
}
*/



