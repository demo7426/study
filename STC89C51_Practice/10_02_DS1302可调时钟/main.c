/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.17
描  述: 实现DS1302可调时钟
备  注:  
修改记录: 

  1.  日期: 2024.11.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "DS1302.h"
#include "LCD1602.h"
#include "Timer0.h"
#include "Key.h"

static unsigned char g_chCurKey = 0;					//当前输入独立按键
static unsigned char g_chSelectIndex = 0;			//当前选择修改的数值位置索引
static unsigned char g_chShowStatus = 0;			//显示状态;0--显示;1--熄灭
static DS1302_TIME g_tDS1302_Time = { 24, 11, 17, 22, 13, 55 };		//初始时间

//设置模式
static void SetMode(void)
{	
	if(g_chCurKey == 3)												//增加数量
	{		
		if(g_chSelectIndex == 0)
		{
			g_tDS1302_Time.Year++;
			if(g_tDS1302_Time.Year > 99){ g_tDS1302_Time.Year = 0; };
		}
		if(g_chSelectIndex == 1)
		{
			g_tDS1302_Time.Month++;
			if(g_tDS1302_Time.Month > 12){ g_tDS1302_Time.Month = 1; };
		}
		if(g_chSelectIndex == 2)
		{
			g_tDS1302_Time.Date++;
			if(g_tDS1302_Time.Month == 1 || g_tDS1302_Time.Month == 3 || g_tDS1302_Time.Month == 5 || g_tDS1302_Time.Month == 7 ||
				g_tDS1302_Time.Month == 8 || g_tDS1302_Time.Month == 10 || g_tDS1302_Time.Month == 12)
			{
				g_tDS1302_Time.Date > 31? g_tDS1302_Time.Date = 1: 0;
			}	
			else if(g_tDS1302_Time.Month == 4 || g_tDS1302_Time.Month == 6 || g_tDS1302_Time.Month == 9 || g_tDS1302_Time.Month == 11)
			{
				g_tDS1302_Time.Date > 30? g_tDS1302_Time.Date = 1: 0;
			}
			else if(g_tDS1302_Time.Month == 2)
			{
				!(g_tDS1302_Time.Year % 4) && g_tDS1302_Time.Date > 28? g_tDS1302_Time.Date = 1: 0;
				g_tDS1302_Time.Year % 4 && g_tDS1302_Time.Date > 29? g_tDS1302_Time.Date = 1: 0;
			}			
		}
		if(g_chSelectIndex == 3)
		{
			g_tDS1302_Time.Hour++;
			if(g_tDS1302_Time.Hour > 23){ g_tDS1302_Time.Hour = 0; };
		}
		if(g_chSelectIndex == 4)
		{
			g_tDS1302_Time.Minute++;
			if(g_tDS1302_Time.Minute > 59){ g_tDS1302_Time.Minute = 0; };
		}
		if(g_chSelectIndex == 5)
		{
			g_tDS1302_Time.Sec++;
			if(g_tDS1302_Time.Sec > 59){ g_tDS1302_Time.Sec = 0; };
		}
	}
	else if(g_chCurKey == 4)									//减少数量
	{
		if(g_chSelectIndex == 0)
		{
			g_tDS1302_Time.Year--;
			if(g_tDS1302_Time.Year < 0){ g_tDS1302_Time.Year = 99; };
		}
		if(g_chSelectIndex == 1)
		{
			g_tDS1302_Time.Month--;
			if(g_tDS1302_Time.Month < 1){ g_tDS1302_Time.Month = 12; };
		}
		if(g_chSelectIndex == 2)
		{
			g_tDS1302_Time.Date--;
			if(g_tDS1302_Time.Month == 1 || g_tDS1302_Time.Month == 3 || g_tDS1302_Time.Month == 5 || g_tDS1302_Time.Month == 7 ||
				g_tDS1302_Time.Month == 8 || g_tDS1302_Time.Month == 10 || g_tDS1302_Time.Month == 12)
			{
				g_tDS1302_Time.Date < 1? g_tDS1302_Time.Date = 31: 0;
			}	
			else if(g_tDS1302_Time.Month == 4 || g_tDS1302_Time.Month == 6 || g_tDS1302_Time.Month == 9 || g_tDS1302_Time.Month == 11)
			{
				g_tDS1302_Time.Date < 1? g_tDS1302_Time.Date = 30: 0;
			}
			else if(g_tDS1302_Time.Month == 2)
			{
				!(g_tDS1302_Time.Year % 4) && g_tDS1302_Time.Date < 1? g_tDS1302_Time.Date = 28: 0;
				g_tDS1302_Time.Year % 4 && g_tDS1302_Time.Date < 1? g_tDS1302_Time.Date = 29: 0;
			}			
		}
		if(g_chSelectIndex == 3)
		{
			g_tDS1302_Time.Hour--;
			if(g_tDS1302_Time.Hour < 0){ g_tDS1302_Time.Hour = 23; };
		}
		if(g_chSelectIndex == 4)
		{
			g_tDS1302_Time.Minute--;
			if(g_tDS1302_Time.Minute < 0){ g_tDS1302_Time.Minute = 59; };
		}
		if(g_chSelectIndex == 5)
		{
			g_tDS1302_Time.Sec--;
			if(g_tDS1302_Time.Sec < 0){ g_tDS1302_Time.Sec = 59; };
		}
		
		//防止在设置月份时，月份和天数不对应的情况

		if(g_tDS1302_Time.Month == 1 || g_tDS1302_Time.Month == 3 || g_tDS1302_Time.Month == 5 || g_tDS1302_Time.Month == 7 ||
			g_tDS1302_Time.Month == 8 || g_tDS1302_Time.Month == 10 || g_tDS1302_Time.Month == 12)
		{
			g_tDS1302_Time.Date > 31? g_tDS1302_Time.Date = 1: 0;
		}	
		else if(g_tDS1302_Time.Month == 4 || g_tDS1302_Time.Month == 6 || g_tDS1302_Time.Month == 9 || g_tDS1302_Time.Month == 11)
		{
			g_tDS1302_Time.Date > 30? g_tDS1302_Time.Date = 1: 0;
		}
		else if(g_tDS1302_Time.Month == 2)
		{
			!(g_tDS1302_Time.Year % 4) && g_tDS1302_Time.Date > 28? g_tDS1302_Time.Date = 1: 0;
			g_tDS1302_Time.Year % 4 && g_tDS1302_Time.Date > 29? g_tDS1302_Time.Date = 1: 0;
		}			
	}
	
	//实现在设置对应值时的闪烁效果
	if(g_chShowStatus)
	{
		g_chSelectIndex == 0? LCD_ShowString(1, 1, "  "): 0;
		g_chSelectIndex == 1? LCD_ShowString(1, 4, "  "): 0;
		g_chSelectIndex == 2? LCD_ShowString(1, 7, "  "): 0;
		g_chSelectIndex == 3? LCD_ShowString(2, 1, "  "): 0;
		g_chSelectIndex == 4? LCD_ShowString(2, 4, "  "): 0;
		g_chSelectIndex == 5? LCD_ShowString(2, 7, "  "): 0;
	}
	else
	{
		LCD_ShowNum(1, 1,  g_tDS1302_Time.Year, 2);
		LCD_ShowNum(1, 4,  g_tDS1302_Time.Month, 2);
		LCD_ShowNum(1, 7,  g_tDS1302_Time.Date, 2);
		LCD_ShowNum(2, 1,  g_tDS1302_Time.Hour, 2);
		LCD_ShowNum(2, 4,  g_tDS1302_Time.Minute, 2);
		LCD_ShowNum(2, 7,  g_tDS1302_Time.Sec, 2);
	}
	
	SetCurTime(g_tDS1302_Time);
}

//显示模式
static void ShowMode(void)
{	
	g_chSelectIndex = 0;
	
	GetCurTime(&g_tDS1302_Time);
	LCD_ShowNum(1, 1,  g_tDS1302_Time.Year, 2);
	LCD_ShowNum(1, 4,  g_tDS1302_Time.Month, 2);
	LCD_ShowNum(1, 7,  g_tDS1302_Time.Date, 2);
	LCD_ShowNum(2, 1,  g_tDS1302_Time.Hour, 2);
	LCD_ShowNum(2, 4,  g_tDS1302_Time.Minute, 2);
	LCD_ShowNum(2, 7,  g_tDS1302_Time.Sec, 2);
}

int main(void)
{
	unsigned char chCurMode = 0;			//当前模式;0--显示模式;1--设置模式;
	
	//初始化操作
	DS1302_Init();
	LCD_Init();
	Timer0_Init();
	
	LCD_ShowString(1, 1, "  -  -");
	LCD_ShowString(2, 1, "  :  :");
	
	SetCurTime(g_tDS1302_Time);
	
	while(1)
	{
		g_chCurKey = GetCurKey();
		
		switch(g_chCurKey)
		{
			case 1:
				chCurMode = !chCurMode;
				break;
			case 2:
				if(chCurMode == 1)
				{
					++g_chSelectIndex;
					g_chSelectIndex = g_chSelectIndex % 6;
				}
				break;
			default:
				break;
		}
		
		chCurMode == 0? ShowMode(): SetMode();
	}
	
	return 0;
}

//定时器0的中断函数
void Timer0_Rountime(void) interrupt 1
{
	static int nCount = 0;
	
	TL0 = 0x20;		//设置定时初值
	TH0 = 0xD1;		//设置定时初值
	
	nCount++;
	if(nCount >= 500)
	{
		g_chShowStatus = !g_chShowStatus;
		nCount = 0;
	}
}
