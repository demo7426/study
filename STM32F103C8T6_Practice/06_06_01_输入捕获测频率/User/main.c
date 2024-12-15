/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.07
描  述: 实现对定时器外部时钟的计数
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
#include "PWM.h"
#include "Delay.h"
#include "IC.h"

int main(void)
{
	OLED_Init();
	PWM_Init();
	IC_Init();
	
	PWM_SetPrescaler(720 - 1);
	PWM_SetCompare1(50);
	
	OLED_ShowString(1, 1, "Freq:000000Hz");
	
	while(1)
	{
		OLED_ShowNum(1, 6, IC_GetFreq(), 6);
	}
}

