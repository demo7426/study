/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.04
描  述: 独立看门狗
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
	
	OLED_ShowString(1, 1, "IWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)
	{
		OLED_ShowString(2, 1, "IWDGRST");
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
	
	//独立看门狗初始化
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(2499);							//1000ms
	IWDG_ReloadCounter();
	IWDG_Enable();
	
	while(1)
	{
		Key_GetCurKey();
		
		IWDG_ReloadCounter();						//喂狗
		
		OLED_ShowString(3, 1, "FEED");
		Delay_ms(400);
		OLED_ShowString(3, 1, "    ");
		Delay_ms(400);
	}
}
