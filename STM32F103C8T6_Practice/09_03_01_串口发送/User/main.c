/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.22
描  述: 使用stm的串口向电脑端发送数据
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
	unsigned char uchArr[4] = { 0x42, 0x43, 0x44, 0x45 };
	
	OLED_Init();
	Serial_Init();
	
	Serial_SendByte(0x41);
	Serial_SendString("\r\n");

	Serial_SendArray(uchArr, 4);
	Serial_SendString("\r\n");
	
	Serial_SendNumber(119, 3);
	Serial_SendString("\r\n");
	
	Serial_Printf("Num = %d\r\n", 99);
	printf("Num = %d\r\n", 100);
	
	while(1)
	{
	}
}
