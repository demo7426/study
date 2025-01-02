/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.01
描  述: 读取实时时钟，未触发RCC的Alram中断时，处于待机模式
备  注: 多次重新下载此程序，需要先按住STM32最小系统板的复位键，再点击程序下载按钮后，然后立刻放开复位键;
修改记录: 

  1.  日期: 2025.01.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Key.h"
#include "MyRTC.h"
#include "Delay.h"

int main(void)
{
	uint32_t unAlarm = 0;											//闹钟时刻
	
	OLED_Init();
	MyRTC_Init();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);				//使能电源时钟
	
	OLED_ShowString(1, 1, "CNT :");
	OLED_ShowString(2, 1, "ALR :  :  :");
	OLED_ShowString(3, 1, "ALRF:");
	
	unAlarm = RTC_GetCounter() + 10;
	RTC_SetAlarm(unAlarm);
	OLED_ShowNum(2, 6, unAlarm, 10);
	
	
	while(1)
	{
		MyRTC_GetTime();
	
		OLED_ShowNum(1, 6, RTC_GetCounter(), 10);
		OLED_ShowNum(3, 6, RTC_GetFlagStatus(RTC_FLAG_ALR), 1);
		
		OLED_ShowString(4, 1, "Running");
		Delay_ms(200);
		OLED_ShowString(4, 1, "       ");
		Delay_ms(200);
		
		OLED_ShowString(4, 9, "STANDBY");
		Delay_ms(1000);
		OLED_ShowString(4, 9, "       ");
		Delay_ms(200);
		
		OLED_Clear();
			
		PWR_EnterSTANDBYMode();					//进入待机模式
	}
}
