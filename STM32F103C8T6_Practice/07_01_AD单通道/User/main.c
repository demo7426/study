/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.17
描  述: 单通道的模拟电压采集，并且显示
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
	unsigned short usAD_Data = 0;
	float fCurVol = 0;					//当前电压值
		
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1, 1, "ADValue:");
	OLED_ShowString(2, 1, "Voltage:0.00V");
	
	while(1)
	{
		usAD_Data = AD_GetValue();
		fCurVol = (float)usAD_Data / 4095 * 3.3;	
		
		OLED_ShowNum(1, 9, usAD_Data, 4);
		OLED_ShowNum(2, 9, fCurVol, 1);
		OLED_ShowNum(2, 11, (unsigned short)(fCurVol * 100) % 100, 2);
		
		Delay_ms(400);
	}
}
