/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.01
描  述: 读取实时时钟
备  注:  
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

int main(void)
{
	OLED_Init();
	MyRTC_Init();
	
	OLED_ShowString(1, 1, "Date:    -  -");
	OLED_ShowString(2, 1, "Time:  :  :");
	OLED_ShowString(3, 1, "CNT :");
	OLED_ShowString(4, 1, "DIV :");
	
	while(1)
	{
		MyRTC_GetTime();
		
		OLED_ShowNum(1, 6, g_usCurTime[0], 4);
		OLED_ShowNum(1, 11, g_usCurTime[1], 2);
		OLED_ShowNum(1, 14, g_usCurTime[2], 2);
		OLED_ShowNum(2, 6, g_usCurTime[3], 2);
		OLED_ShowNum(2, 9, g_usCurTime[4], 2);
		OLED_ShowNum(2, 12, g_usCurTime[5], 2);
		
		OLED_ShowNum(3, 6, RTC_GetCounter(), 10);
		OLED_ShowNum(4, 6, RTC_GetDivider(), 10);
	}
}
