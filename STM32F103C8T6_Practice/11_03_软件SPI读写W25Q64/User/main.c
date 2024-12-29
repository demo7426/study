/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.29
描  述: 使用软件SPI读写W25Q64
备  注:  
修改记录: 

  1.  日期: 2024.12.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "W25Q64.h"

int main(void)
{
	uint8_t uchMID = 0;					//制造商ID
	uint16_t usDID = 0;					//设备ID
	uint8_t uchWriteData[] = { 0x01, 0x02, 0x03, 0x04 };
	uint8_t uchReadData[4] = { 0 };
	
	OLED_Init();
	W25Q64_Init();
	
	OLED_ShowString(1, 1, "MID:   DID:");
	OLED_ShowString(2, 1, "W:");
	OLED_ShowString(3, 1, "R:");
	
	W25Q64_ReadID(&uchMID, &usDID);
	
	OLED_ShowHexNum(1, 5, uchMID, 2);
	OLED_ShowHexNum(1, 12, usDID, 4);
	
	W25Q64_SectorErase(0x000000);
	
	W25Q64_PageProgram(0x000000, uchWriteData, 4);
	W25Q64_ReadData(0x000000, uchReadData, 4);
	
	OLED_ShowHexNum(2, 3, uchWriteData[0], 2);
	OLED_ShowHexNum(2, 6, uchWriteData[1], 2);
	OLED_ShowHexNum(2, 9, uchWriteData[2], 2);
	OLED_ShowHexNum(2, 12, uchWriteData[3], 2);
	
	OLED_ShowHexNum(3, 3, uchReadData[0], 2);
	OLED_ShowHexNum(3, 6, uchReadData[1], 2);
	OLED_ShowHexNum(3, 9, uchReadData[2], 2);
	OLED_ShowHexNum(3, 12, uchReadData[3], 2);
	
	while(1)
	{
	}
}
