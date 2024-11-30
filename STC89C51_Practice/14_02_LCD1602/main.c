/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.30
描  述: LCD1602显示字符串和数字
备  注:  
修改记录: 

  1.  日期: 2024.11.30
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "LCD1602.h"
#include "Delay.h"

int main(void)
{
	LCD_Init();
	LCD_ShowChar(1, 1, 'A');
	LCD_ShowString(1, 3, "Temp");
	LCD_ShowNum(1, 8, 20, 2);
	LCD_ShowSignedNum(1, 11, -31, 2);
	LCD_ShowHexNum(2, 1, 0x65, 2);
	LCD_ShowBinNum(2, 4, 0x12, 8);
	
	LCD_WriteData(0xDF);
	
	LCD_ShowString(1, 15, "Hello world!");
	
	while(1)
	{
		LCD_WriteCommand(0x18);			//向左移屏指令
		Delay(500);
	}
	
	return 0;
}
