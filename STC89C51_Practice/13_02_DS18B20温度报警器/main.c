/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Buzzer.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.29
描  述: DS18B20温度报警器
备  注:  
修改记录: 

  1.  日期: 2024.11.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/
#include <REGX52.H>

#include "LCD1602.h"
#include "DS18B20.h"
#include "Delay.h"
#include "Timer0.h"
#include "Key.h"

char g_chLowTemp = 15;				//低温阈值
char g_chHighTemp = 25;				//高温阈值

int main(void)
{
	float fCurTemp, fShowTemp;			//当前温度
	int nCurKey = 0;
	
	DS18B20_Convert();
	Delay(1000);
	
	LCD_Init();
	Timer0_Init();
		
	LCD_ShowString(1, 1, "T:");
	LCD_ShowString(2, 1, "L:");
	LCD_ShowString(2, 8, "H:");
	LCD_ShowSignedNum(2, 3, g_chLowTemp, 3);
	LCD_ShowSignedNum(2, 10, g_chHighTemp, 3);
	
	while(1)
	{
		DS18B20_Convert();
		fCurTemp = DS18B20_GetCurTemp();
		fShowTemp = fCurTemp;
		
		if(fShowTemp < 0)
		{
			LCD_ShowChar(1, 3, '-');
			fShowTemp = -fShowTemp;
		}
		else
			LCD_ShowChar(1, 3, '+');
		
		LCD_ShowNum(1, 4, fShowTemp, 3);
		LCD_ShowChar(1, 7, '.');
		LCD_ShowNum(1, 8, (unsigned long)(fShowTemp * 10000) % 10000, 4);
		
		//处理有独立按键输入的情况
		nCurKey = GetCurKey();
		if(nCurKey == 1)
		{
			if(g_chLowTemp >= -100)
				g_chLowTemp--;
		}
		else if(nCurKey == 2)
		{
			g_chLowTemp++;
			if(g_chLowTemp >= g_chHighTemp)
				g_chLowTemp--;
		}
		else if(nCurKey == 3)
		{
			g_chHighTemp--;
			if(g_chHighTemp <= g_chHighTemp)
				g_chHighTemp++;
		}
		else if(nCurKey == 4)
		{
			if(g_chLowTemp <= 200)
				g_chLowTemp++;
		}
		
		if(nCurKey != 0)
		{
			LCD_ShowSignedNum(2, 3, g_chLowTemp, 3);
			LCD_ShowSignedNum(2, 10, g_chHighTemp, 3);
		}
		
		//温度阈值判断
		if(fCurTemp <= g_chLowTemp)
			LCD_ShowString(1, 13, "OV:L");
		else if(fCurTemp >= g_chHighTemp)
			LCD_ShowString(1, 13, "OV:H");
		else
			LCD_ShowString(1, 13, "    ");
	}
	
	return 0;
}

//定时器0的中断函数模板
void Timer0_Rountime(void) interrupt 1
{
	static unsigned int unKeyCount = 0;
	
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	
	unKeyCount++;
	if(unKeyCount > 20)			//选择20ms是为了对独立按键进行软件消抖
	{
		unKeyCount = 0;
		KeyLoop();
	}
}