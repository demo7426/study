/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.02
描  述: 实现红外对射传感器计数显示，在不工作时，进入停止模式
备  注:  
修改记录: 

  1.  日期: 2025.01.02
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "CountSensor.h"
#include "Delay.h"

int main(void)
{
	OLED_Init();
	CountSensor_Init();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);				//使能电源时钟
	
	OLED_ShowString(1, 1, "Num:");
	
	while(1)
	{
		OLED_ShowNum(1, 5, CountSensor_GetCurCount(), 5);
		
		OLED_ShowString(2, 1, "Running");
		Delay_ms(200);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(200);
		
		PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);		//进入停止模式
		SystemInit();												//重新将8MHz的时钟，通过PLL锁相环倍频到75MHz
	}
}
