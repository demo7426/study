/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.17
描  述: 实现DS1302实时时钟显示
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

int main(void)
{
	DS1302_TIME tDS1302_Time = { 24, 11, 17, 20, 56, 55 };
	
	DS1302_Init();
	LCD_Init();
	
	LCD_ShowString(1, 1, "  -  -");
	LCD_ShowString(2, 1, "  :  :");
	
	SetCurTime(tDS1302_Time);
	
	while(1)
	{
		GetCurTime(&tDS1302_Time);
		LCD_ShowNum(1, 1,  tDS1302_Time.Year, 2);
		LCD_ShowNum(1, 4,  tDS1302_Time.Month, 2);
		LCD_ShowNum(1, 7,  tDS1302_Time.Date, 2);
		LCD_ShowNum(2, 1,  tDS1302_Time.Hour, 2);
		LCD_ShowNum(2, 4,  tDS1302_Time.Minute, 2);
		LCD_ShowNum(2, 7,  tDS1302_Time.Sec, 2);
	}
	
	return 0;
}

