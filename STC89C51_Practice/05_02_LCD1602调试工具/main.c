/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.11
描  述: 调试LCD1602显示屏
备  注:  
修改记录: 

  1.  日期: 2024.11.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "LCD1602.h"

int main(void)
{
	LCD_Init();
	
	LCD_ShowChar(1, 1, 'A');
	LCD_ShowString(1, 3, "Hello");
	LCD_ShowNum(1, 9, 12, 2);
	LCD_ShowSignedNum(1, 13, -34, 2);
	LCD_ShowHexNum(2, 1, 0xEF, 2);
	LCD_ShowBinNum(2, 6, 0x10, 8);
	
	while(1);
	
	return 0;
}
