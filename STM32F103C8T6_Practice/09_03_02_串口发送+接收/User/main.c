/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.22
描  述: 电脑端向stm串口发送数据，串口数据回环
备  注:  
修改记录: 

  1.  日期: 2024.12.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Serial.h"

int main(void)
{
	uint8_t uchRxData = 0;
	
	OLED_Init();
	Serial_Init();
	
	while(1)
	{
		if(Serial_GetRxFlag())
		{
			uchRxData = Serial_GetRxData();
			
			Serial_SendByte(uchRxData);
			OLED_ShowHexNum(1, 1, uchRxData, 2);
		}
	}
}
