/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.25
描  述: CAN总线回环测试
备  注:  
修改记录: 

  1.  日期: 2025.11.25
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Key.h"
#include "MyCAN.h"

int main(void)
{
	uint8_t uchKeyNum = 0;
	
	const uint32_t unTxID = 0x555;											//发送ID
	uint8_t uchTxData[4] = {0x00, 0x01, 0x02, 0x03};		//发送数据缓冲区
	
	uint32_t unRxID = 0;																//接收ID
	uint8_t uchRxLength = 0;														//接收数据的有效长度
	uint8_t uchRxData[8] = { 0 }; 											//接收数据缓冲区
	
	OLED_Init();
	Key_Init();
	MyCAN_Init();
	
	OLED_ShowString(2, 1, "RxID:");
	OLED_ShowString(3, 1, "Leng:");
	OLED_ShowString(4, 1, "Data:");
	
	while(1)
	{
		uchKeyNum = Key_GetCurKey();
		
		if(uchKeyNum == 1)
		{
			MyCAN_Transmit(unTxID, uchTxData, 4);
			
			uchTxData[0]++;
			uchTxData[1]++;
			uchTxData[2]++;
			uchTxData[3]++;
		}
		
		if(MyCAN_ReceiveFlag() == 1)
		{
			MyCAN_Receive(&unRxID, uchRxData, &uchRxLength);
			
			OLED_ShowHexNum(2, 6, unRxID, 3);
			OLED_ShowHexNum(3, 6, uchRxLength, 1);
			OLED_ShowHexNum(4, 6, uchRxData[0], 2);
			OLED_ShowHexNum(4, 9, uchRxData[1], 2);
			OLED_ShowHexNum(4, 12, uchRxData[2], 2);
			OLED_ShowHexNum(4, 15, uchRxData[3], 2);
		}
	}
}
