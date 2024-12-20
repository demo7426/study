/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.20
描  述: DMA数据转运
备  注:  
修改记录: 

  1.  日期: 2024.12.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "MyDMA.h"
#include "Delay.h"

int main(void)
{
	unsigned char uchArr01[4] = { 0x01, 0x02, 0x03, 0x04 };
	unsigned char uchArr02[4] = { 0 };
	
	OLED_Init();
		
	MyDMA_Init((unsigned int)uchArr01, (unsigned int)uchArr02, 4);
	
	OLED_ShowString(1, 1, "Arr01:");
	OLED_ShowHexNum(1, 9, (unsigned int)uchArr01, 8);
	OLED_ShowString(3, 1, "Arr02:");
	OLED_ShowHexNum(3, 9, (unsigned int)uchArr02, 8);
	
	while(1)
	{
		uchArr01[0]++;
		uchArr01[1]++;
		uchArr01[2]++;
		uchArr01[3]++;
		
		OLED_ShowHexNum(2, 1, uchArr01[0], 2);
		OLED_ShowHexNum(2, 4, uchArr01[1], 2);
		OLED_ShowHexNum(2, 7, uchArr01[2], 2);
		OLED_ShowHexNum(2, 10, uchArr01[3], 2);
		Delay_ms(1000);
		
		MyDMA_Transfer();
		
		OLED_ShowHexNum(4, 1, uchArr02[0], 2);
		OLED_ShowHexNum(4, 4, uchArr02[1], 2);
		OLED_ShowHexNum(4, 7, uchArr02[2], 2);
		OLED_ShowHexNum(4, 10, uchArr02[3], 2);
		Delay_ms(1000);
	}
}
