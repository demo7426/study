/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.02
描  述: AD模数转换
备  注:  
修改记录: 

  1.  日期: 2024.12.02
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "Delay.h"
#include "LCD1602.h"
#include "XPT2046.h"

int main(void)
{
	unsigned int unReadAD = 0;
	
	LCD_Init();
	
	LCD_ShowString(1, 1, "ADJ  NTC  RG");
	while(1)
	{
		unReadAD = XPT2046_ReadCurAD(XPT2046_XP_12);
		LCD_ShowNum(2, 1, unReadAD, 4);
		unReadAD = XPT2046_ReadCurAD(XPT2046_YP_12);
		LCD_ShowNum(2, 6, unReadAD, 4);
		unReadAD = XPT2046_ReadCurAD(XPT2046_VBAT_8);
		LCD_ShowNum(2, 11, unReadAD, 4);
	}
	
	return 0;
}

