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
	uint32_t unTxMsgIndex = 0;
	
	//发送信息
	CanTxMsg tCanTxMsg[] = {
		//StdId 	ExtId       IDE              RTR           DLC	Data[8]
		{0x123, 0x12345600, CAN_Id_Standard, CAN_RTR_Data, 		4, 	{ 0x00, 0x01, 0x02, 0x03}},
		{0x234, 0x12345678, CAN_Id_Standard, CAN_RTR_Data, 		4, 	{ 0x00, 0x01, 0x02, 0x03}},
		{0x000, 0x12345600, CAN_Id_Extended, CAN_RTR_Data, 		4, 	{ 0x00, 0x01, 0x02, 0x03}},
		{0x000, 0x12345678, CAN_Id_Extended, CAN_RTR_Data, 		4, 	{ 0x00, 0x01, 0x02, 0x03}},
		{0x000, 0x0789AB00, CAN_Id_Extended, CAN_RTR_Data, 		4, 	{ 0x00, 0x01, 0x02, 0x03}},
		{0x000, 0x0789ABCD, CAN_Id_Extended, CAN_RTR_Data, 		4, 	{ 0x00, 0x01, 0x02, 0x03}},
		{0x000, 0x0789AC00, CAN_Id_Extended, CAN_RTR_Data, 		4, 	{ 0x00, 0x01, 0x02, 0x03}},
		{0x000, 0x0789ACDE, CAN_Id_Extended, CAN_RTR_Data, 		4, 	{ 0x00, 0x01, 0x02, 0x03}},
	};
		
	//接收信息
	CanRxMsg tCanRxMsg = { 0 };
	
	OLED_Init();
	Key_Init();
	MyCAN_Init();
	
	OLED_ShowString(1, 1, " Rx :");
	OLED_ShowString(2, 1, "RxID:");
	OLED_ShowString(3, 1, "Leng:");
	OLED_ShowString(4, 1, "Data:");
		
	while(1)
	{
		uchKeyNum = Key_GetCurKey();
			
		if(uchKeyNum == 1)
		{
			MyCAN_Transmit(&tCanTxMsg[unTxMsgIndex]);
			
			tCanTxMsg[unTxMsgIndex].Data[0]++;
			tCanTxMsg[unTxMsgIndex].Data[1]++;
			tCanTxMsg[unTxMsgIndex].Data[2]++;
			tCanTxMsg[unTxMsgIndex].Data[3]++;
			
			unTxMsgIndex++;
			unTxMsgIndex = unTxMsgIndex % (sizeof(tCanTxMsg) / sizeof(tCanTxMsg[0]));
		}
		
		if(MyCAN_ReceiveFlag() == 1)
		{
			MyCAN_Receive(&tCanRxMsg);
			
			if(tCanRxMsg.IDE == CAN_Id_Standard)					//标准帧
			{
				OLED_ShowString(1, 6, "Std");
				OLED_ShowHexNum(2, 6, tCanRxMsg.StdId, 8);
			}
			else if(tCanRxMsg.IDE == CAN_Id_Extended)			//扩展帧
			{
				OLED_ShowString(1, 6, "Ext");
				OLED_ShowHexNum(2, 6, tCanRxMsg.ExtId, 8);
			}
			else
			{
				OLED_ShowString(1, 6, "   ");
			}
			
			if(tCanRxMsg.RTR == CAN_RTR_Data)							//数据帧
			{
				OLED_ShowString(1, 10, "Data  ");
				
				OLED_ShowHexNum(3, 6, tCanRxMsg.DLC, 1);
				OLED_ShowHexNum(4, 6, tCanRxMsg.Data[0], 2);
				OLED_ShowHexNum(4, 9, tCanRxMsg.Data[1], 2);
				OLED_ShowHexNum(4, 12, tCanRxMsg.Data[2], 2);
				OLED_ShowHexNum(4, 15, tCanRxMsg.Data[3], 2);
			}
			else if(tCanRxMsg.RTR == CAN_RTR_Remote)			//遥控帧
			{
				OLED_ShowString(1, 10, "Remote");
				
				OLED_ShowHexNum(3, 6, 0, 1);
				OLED_ShowHexNum(4, 6, 0x00, 2);
				OLED_ShowHexNum(4, 9, 0x00, 2);
				OLED_ShowHexNum(4, 12, 0x00, 2);
				OLED_ShowHexNum(4, 15, 0x00, 2);
			}
			else
			{
				OLED_ShowString(1, 10, "      ");
			}
		}
		
	}
}
