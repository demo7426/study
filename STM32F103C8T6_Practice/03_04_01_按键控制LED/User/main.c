/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.06
描  述: 按键控制LED灯显示
备  注:  
修改记录: 

  1.  日期: 2024.12.06
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "Delay.h"
#include "LED.h"
#include "Key.h"

int main(void)
{
	unsigned char uchCurKey = 0;
	
	LED_Init();
	Key_Init();
	
	while(1)
	{
		uchCurKey =Key_GetCurKey();
		
		if(uchCurKey == 1)
		{
			LED_Turn_01();
		}
		else if(uchCurKey == 2)
		{
			LED_Turn_02();
		}
	}
}
