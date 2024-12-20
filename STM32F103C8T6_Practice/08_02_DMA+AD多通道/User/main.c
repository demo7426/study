/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.17
描  述: 多通道的模拟电压采集，并且显示
备  注:  
修改记录: 

  1.  日期: 2024.12.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "AD.h"
#include "Delay.h"

int main(void)
{
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1, 1, "AD0:");
	OLED_ShowString(2, 1, "AD1:");
	OLED_ShowString(3, 1, "AD2:");
	OLED_ShowString(4, 1, "AD3:");
	
	while(1)
	{
#ifndef AD_CONTI_TRANSFER
		AD_GetValue();
#endif
		OLED_ShowNum(1, 5, g_usAD_Value[0], 4);		
		OLED_ShowNum(2, 5, g_usAD_Value[1], 4);		
		OLED_ShowNum(3, 5, g_usAD_Value[2], 4);
		OLED_ShowNum(4, 5, g_usAD_Value[3], 4);
		
		Delay_ms(200);
	}
}
