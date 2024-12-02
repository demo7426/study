/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.02s
描  述: DA数模转换
备  注:  
修改记录: 

  1.  日期: 2024.12.02
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/
#include <REGX52.H>

#include "Key.h"
#include "Delay.h"
#include "NixieTube.h"
#include "Timer0.h"
#include "LCD1602.h"

#define DA P2_1

static unsigned int g_unCompValue = 0;			//比较值

int main(void)
{
	int i = 0;
	
	Timer0_Init();
	
	while(1)
	{
		for(i = 0; i < 100; i++)
		{
			g_unCompValue = i;
			Delay(1);
		}
		
		for(i = 100; i > 0; i--)
		{
			g_unCompValue = i;
			Delay(1);
		}
	}
	
	return 0;
}

//定时器0的中断函数;100us
void Timer0_Rountime(void) interrupt 1
{
	static unsigned int unKeyCounter = 0;
	static unsigned int unCounter = 0;
	static unsigned int unNixieTubeCount = 0;			//数码管计数
	
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	
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
		DA = 0;
	}
	else if(unCounter <= g_unCompValue)
	{
		DA = 1;
	}
}
