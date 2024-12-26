/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.07
描  述: OLED显示数据
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
#include "Delay.h"
#include "MPU6050.h"


int main(void)
{
	int16_t usAccX, usAccY, usAccZ, usGyroX, usGyroY, usGyroZ;
	
	OLED_Init();
	MPU6050_Init();
	
	OLED_ShowString(1, 1, "ID:0x");
	OLED_ShowHexNum(1, 6, MPU6050_GetID(), 2);
	
	while(1)
	{
		MPU6050_GetData(&usAccX, &usAccY, &usAccZ, &usGyroX, &usGyroY, &usGyroZ);
		
		OLED_ShowSignedNum(2, 1, usAccX, 5);
		OLED_ShowSignedNum(3, 1, usAccY, 5);
		OLED_ShowSignedNum(4, 1, usAccZ, 5);
		OLED_ShowSignedNum(2, 8, usGyroX, 5);
		OLED_ShowSignedNum(3, 8, usGyroY, 5);
		OLED_ShowSignedNum(4, 8, usGyroZ, 5);
		
		Delay_ms(200);
	}
}
