/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Buzzer.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.28
描  述: DS18B20温度读取
备  注:  
修改记录: 

  1.  日期: 2024.11.28
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "LCD1602.h"
#include "DS18B20.h"
#include "Delay.h"

int main(void)
{
	float fCurTemp = 0;			//当前温度
	
	DS18B20_Convert();
	Delay(1000);
	
	LCD_Init();
		
	while(1)
	{
		DS18B20_Convert();
		fCurTemp = DS18B20_GetCurTemp();
		
		if(fCurTemp < 0)
		{
			LCD_ShowChar(1, 1, '-');
			fCurTemp = -fCurTemp;
		}
		else
			LCD_ShowChar(1, 1, '+');
		
		LCD_ShowNum(1, 1, fCurTemp, 3);
		LCD_ShowChar(1, 4, '.');
		LCD_ShowNum(1, 5, (unsigned long)(fCurTemp * 10000) % 10000, 4);
	}
	
	return 0;
}

