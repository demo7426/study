/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.04
描  述: 窗口看门狗
备  注:  
修改记录: 

  1.  日期: 2025.01.04
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Delay.h"
#include "Key.h"

int main(void)
{
	OLED_Init();
	Key_Init();
	
	OLED_ShowString(1, 1, "WWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET)
	{
		OLED_ShowString(2, 1, "WWDGRST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(100);
	}
	else
	{
		OLED_ShowString(2, 1, "RST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "   ");
		Delay_ms(100);
	}
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	//窗口看门狗初始化
	WWDG_SetPrescaler(WWDG_Prescaler_8);		//设置最大分频，窗口看门狗可以设置最大时间限度
	WWDG_SetWindowValue(0x40 | 21);				//30ms
	WWDG_Enable(0x40 | 54);						//50ms
	
	while(1)
	{
		Key_GetCurKey();
		
		OLED_ShowString(3, 1, "FEED");
		Delay_ms(20);
		OLED_ShowString(3, 1, "    ");
		Delay_ms(20);
		
		WWDG_SetCounter(0x40 | 54);				//喂狗
	}
}
