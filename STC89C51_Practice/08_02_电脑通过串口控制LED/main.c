/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.14
描  述: 电脑通过串口控制LED
备  注:  
修改记录: 

  1.  日期: 2024.11.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "UART.h"

int main(void)
{
	UART_Init();
	
	while(1){}
	
	return 0;
}

void UART_Rountine(void)	interrupt 4
{
	if(RI == 1)				//接收数据
	{
		P2 = SBUF;
		UART_SendByte(SBUF);
		RI = 0;
	}
}