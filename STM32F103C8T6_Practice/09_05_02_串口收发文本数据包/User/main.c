/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.22
描  述: 电脑端发送数据，控制LED灯的亮灭
备  注:  
修改记录: 

  1.  日期: 2024.12.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/
#include <string.h>
#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Serial.h"
#include "Key.h"
#include "LED.h"

int main(void)
{
	uint8_t uchSendData[4] = { 0x41, 0x42, 0x43, 0x44 };
	uint8_t* puchRecvData = NULL;
	uint16_t usRecvSize = 0;
	
	OLED_Init();
	Serial_Init();
	Key_Init();
	LED_Init();
	
	OLED_ShowString(1, 1, "COMMAND:");	
	OLED_ShowString(3, 1, "TIPS:");
	
	while(1)
	{
		if(Key_GetCurKey() == 1)
		{
			Serial_SendPacket(uchSendData, 4);
		}
		
		if(Serial_GetRxFlag())
		{
			Serial_GetRxData((unsigned char**)&puchRecvData, &usRecvSize);
			
			OLED_ShowString(2, 1, "                ");		
			OLED_ShowString(2, 1, (char*)puchRecvData);		
			
			if(strcmp((const char*)puchRecvData, "LED_ON") == 0)
			{
				OLED_ShowString(4, 1, "                ");
				OLED_ShowString(4, 1, "LED_ON is OK");
				LED_On_01();
			}		
			else if(strcmp((const char*)puchRecvData, "LED_OFF") == 0)
			{
				OLED_ShowString(4, 1, "                ");
				OLED_ShowString(4, 1, "LED_OFF is OK");
				LED_Off_01();
			}		
			else
			{
				OLED_ShowString(4, 1, "                ");
				OLED_ShowString(4, 1, "COMMAND is ERR");			
			}
		}
	}
}
