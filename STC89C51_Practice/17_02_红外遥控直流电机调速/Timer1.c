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

#include "Timer1.h"
#include "Key.h"
#include "NixieTube.h"

#define MONITOR P1_0

static unsigned int g_unCompValue = 0;			//比较值

void Timer1_Init(void)
{
	//设置定时器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x9C;		//设置定时初值
	TH1 = 0xFF;		//设置定时初值
	TF1 = 0;		//清除TF0标志
	TR1 = 1;		//定时器0开始计时
	
	//开启Timer0对应的中断
	ET1 = 1;
	EA = 1;
	PT1 = 0;
}

void Timer1_SetCurSpeed(unsigned char _Speed)
{
	g_unCompValue = _Speed;
}

//定时器1的中断函数;100us
void Timer1_Rountime(void) interrupt 3
{
	static unsigned int unKeyCounter = 0;
	static unsigned int unCounter = 0;
	static unsigned int unNixieTubeCount = 0;			//数码管计数
	
	TL1 = 0xA4;		//设置定时初值
	TH1 = 0xFF;		//设置定时初值
	
	//独立按键调用
	unKeyCounter++;
	if(unKeyCounter >= 200)
	{
		unKeyCounter = 0;
		KeyLoop();
	}
			
	unNixieTubeCount++;
	if(unNixieTubeCount >= 20)
	{
		unNixieTubeCount = 0;
		
		NixieTubeLoop();
	}
	
	unCounter++;
	unCounter %= 100;
	if(unCounter > g_unCompValue)
	{
		MONITOR = 0;
	}
	else if(unCounter <= g_unCompValue)
	{
		MONITOR = 1;
	}
}


//定时器1的中断函数模板
//void Timer1_Rountime(void) interrupt 3
//{
//	TL1 = 0xAE;		//设置定时初值
//	TH1 = 0xFB;		//设置定时初值
//}
