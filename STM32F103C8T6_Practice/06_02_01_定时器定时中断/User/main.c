/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.07
描  述: 使用定时器中断的进行计数
备  注:  
修改记录: 

  1.  日期: 2024.12.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Timer.h"

static int g_nCount = 0;

int main(void)
{
	OLED_Init();
	Timer_Init();
	
	OLED_ShowString(1, 1, "Num:");
	
	while(1)
	{
		OLED_ShowSignedNum(2, 1, g_nCount, 5);
		OLED_ShowSignedNum(3, 1, TIM_GetCounter(TIM2), 5);
		OLED_ShowSignedNum(4, 1, TIM_GetPrescaler(TIM2), 5);
	}
}

//定时器2中断模板
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		g_nCount++;
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);						//清除对应中断标志位
	}
}
