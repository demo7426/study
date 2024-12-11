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
#include "Servo.h"
#include "Key.h"

int main(void)
{
	unsigned char uchCurKey = 0;
	float fAngle = 0;
	
	Key_Init();
	Servo_Init();
	
	while(1)
	{
		uchCurKey = Key_GetCurKey();
		if(uchCurKey == 1)
		{
			fAngle += 30;
			fAngle > 180? fAngle = 0: 0;
			
			Servo_SetAngle(fAngle);
		}
	}
}

