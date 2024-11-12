/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.11
描  述: 实现一个矩阵键盘密码锁
备  注:  
修改记录: 

  1.  日期: 2024.11.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>
#include <INTRINS.H>

#include "Timer0.h"
#include "LCD1602.h"

static int g_nSec = 0;			//秒钟
static int g_nMin = 0;			//分钟
static int g_nHour = 0;			//小时

int main(void)
{
	int nCurKey = 0;
	
	LCD_Init();
	Timer0_Init();
	
	LCD_ShowString(1, 1, "Clock:");
	LCD_ShowString(2, 1, "  :  :");
	while(1)
	{
		LCD_ShowNum(2, 1, g_nHour, 2);
		LCD_ShowNum(2, 4, g_nMin, 2);
		LCD_ShowNum(2, 7, g_nSec, 2);
	}
	
	return 0;
}

void Timer0_Rountime(void) interrupt 1
{
	static int nCount = 0;
	
	nCount++;
	
	TL0 = 0x20;		//设置定时初值
	TH0 = 0xD1;		//设置定时初值
	
	if(nCount >= 1000)
	{
		nCount = 0;
		
		//累加时间
		g_nSec++;
		if(g_nSec>=60)
		{
			g_nSec = 0;
			g_nMin++;
			if(g_nMin>=60)
			{
				g_nMin = 0;
				g_nHour++;
				if(g_nHour == 24)
					g_nHour = 0;
			}
		}
	}
}
