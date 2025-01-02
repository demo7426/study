/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.02
描  述: 修改主频
备  注: 直接将SYSCLK_FREQ_72MHz宏替换为其它即可，比如SYSCLK_FREQ_36MHz
修改记录: 

  1.  日期: 2025.01.02
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Delay.h"

int main(void)
{
	OLED_Init();
	
	OLED_ShowString(1, 1, "SysClk:");
	OLED_ShowNum(1, 8, SystemCoreClock, 8);
	
	while(1)
	{
		OLED_ShowString(2, 1, "Running");
		Delay_ms(500);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(500);
	}
}
