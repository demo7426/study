/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.13
描  述: 实现串口向电脑发送数据
备  注:  
修改记录: 

  1.  日期: 2024.11.13
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "Delay.h"

void UART_Init(void)
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFA;			//设定定时初值
	TH1 = 0xFA;			//设定定时器重装值
	ET1 = 0;				//禁止定时器1中断
	TR1 = 1;				//启动定时器1
	
	//关闭串口中断
	EA = 1;
	ES = 0;
	
	//使用默认的串口中断优先级
}

//串口发送数据
void UART_SendByte(char _Value)
{
	SBUF = _Value;		
}

int main(void)
{
	UART_Init();
	
	while(1)
	{
		UART_SendByte('A');
		Delay(1000);
	}
	
	return 0;
}