/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Timer0.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.12
描  述: 定时器0模块
备  注:  
修改记录: 

  1.  日期: 2024.11.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "Timer0.h"

void Timer0_Init(void)
{
	//设置定时器
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0;		//设置定时初值
	TH0 = 0;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0开始计时
}

void Timer0_SetCounter(unsigned int _Counter)
{
	TH0 = _Counter / 256;		//设置定时初值
	TL0 = _Counter % 256;		//设置定时初值
}

unsigned int Timer0_GetCounter(void)
{
	return (TH0 << 8) | TL0;
}

void Timer0_Run(unsigned char _Flag)
{
	TR0 = _Flag;
}

//定时器0的中断函数模板
//void Timer0_Rountime(void) interrupt 1
//{
//	TL0 = 0xAE;		//设置定时初值
//	TH0 = 0xFB;		//设置定时初值
//}
