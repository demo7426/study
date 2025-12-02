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
#include <math.h>
#include <stdlib.h>
#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Serial.h"
#include "Key.h"
#include "LED.h"
#include "Delay.h"

int main(void)
{
	uint8_t uchSendData[4] = { 0x41, 0x42, 0x43, 0x44 };
	uint8_t* puchRecvData = NULL;
	uint16_t usRecvSize = 0;
	
	char* pchCmd = NULL;
	char* pchName = NULL;
	char* pchAct = NULL;
	char* pchVals[4];
	
#if 0
	float x = 0;
	float y1 = 0;	
	float y2 = 0;
#endif
	
	OLED_Init();
	Serial_Init();
	Key_Init();
	LED_Init();
	
	while(1)
	{
#if 0
		x += 0.1;
		y1 = sin(x);
		y2 = cos(x);
		
		Serial_Printf("[plot,%f,%f]", y1, y2);
		
		Delay_ms(10);
		
		continue;
#endif
		
		if(Key_GetCurKey() == 1)
		{
			Serial_SendPacket(uchSendData, 4);
		}
		
		if(Serial_GetRxFlag())
		{
			Serial_GetRxData((unsigned char**)&puchRecvData, &usRecvSize);
			
			OLED_ShowString(2, 1, "                ");	
			OLED_ShowString(3, 1, "                ");		
			
			pchCmd = strtok((char*)puchRecvData, ",");	
			
			OLED_ShowString(2, 1, (char*)pchCmd);	
			OLED_ShowString(3, 1, (char*)(puchRecvData + strlen(pchCmd) + 1));	
			
			if(strcmp(pchCmd, "led") == 0)
			{
				pchName = strtok(NULL, ",");
				pchAct = strtok(NULL, ",");	
				
				if(strcmp(pchName, "1") == 0 && strcmp(pchAct, "on") == 0)
				{
					LED_On_01();
					Serial_SendString("led,1,on");
				}
				else if(strcmp(pchName, "1") == 0 && strcmp(pchAct, "off") == 0)
				{
					LED_Off_01();
					Serial_SendString("led,1,off");
				}
			}
			else if(strcmp(pchCmd, "slider") == 0)
			{
				pchName = strtok(NULL, ",");
				pchAct = strtok(NULL, ",");	
				
				Serial_Printf("%s,%d,%f", pchCmd, atoi(pchName), atof(pchAct));
			}
			else if(strcmp(pchCmd, "joystick") == 0)
			{
				pchVals[0] = strtok(NULL, ",");
				pchVals[1] = strtok(NULL, ",");
				pchVals[2] = strtok(NULL, ",");
				pchVals[3] = strtok(NULL, ",");
				
				Serial_Printf("%s,%d,%d,%d,%d", pchCmd, atoi(pchVals[0]), atoi(pchVals[1]), atoi(pchVals[2]), atoi(pchVals[3]));
			}
			
			Serial_SendString("\r\n");
			
		}
	}
}
