/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.07
描  述: 实现对定时器外部时钟的计数
备  注:  
修改记录: 

  1.  日期: 2024.12.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Motor.h"
#include "Key.h"

int main(void)
{
	unsigned char uchCurKey = 0;
	int nCurSpeed = 0;
	
	OLED_Init();
	Key_Init();
	Motor_Init();
	
	OLED_ShowString(1, 1, "Speed:");
	
	while(1)
	{
		uchCurKey = Key_GetCurKey();
		if(uchCurKey == 1)
		{
			nCurSpeed += 20;
			
			if(nCurSpeed > 100)
				nCurSpeed = -100;
			
			Servo_SetCurSpeed(nCurSpeed);
		}
		
		OLED_ShowSignedNum(2, 1, nCurSpeed, 3);
	}
}

