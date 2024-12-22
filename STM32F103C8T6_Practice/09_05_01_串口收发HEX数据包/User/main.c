/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.22
描  述: 串口收发HEX数据包
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
#include "Key.h"

int main(void)
{
	uint8_t uchSendData[4] = { 0x41, 0x42, 0x43, 0x44 };
	uint8_t* puchRecvData = NULL;
	uint16_t usRecvSize = 0;
	int i = 0;
	
	OLED_Init();
	Serial_Init();
	Key_Init();
	
	while(1)
	{
		if(Key_GetCurKey() == 1)
		{
			Serial_SendPacket(uchSendData, 4);
		}
		
		if(Serial_GetRxFlag())
		{
			Serial_GetRxData((unsigned char**)&puchRecvData, &usRecvSize);
			
			for(i = 0; i < usRecvSize; i++)
			{
				OLED_ShowHexNum(1, i * 3 + 1, puchRecvData[i], 2);
			}
			
		}
	}
}
