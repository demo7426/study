/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Buzzer.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.24
描  述: 使用I2C总线控制AT24C02进行数据读写;AT24C02为E²PROM
备  注:  
修改记录: 

  1.  日期: 2024.11.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "AT24C02.h"
#include "LCD1602.h"
#include "Key.h"
#include "Delay.h"

int main(void)
{
	unsigned int unCurNum = 0;				//当前数值
	unsigned char uchCurKey = 0;			//当前输入独立按键
	
	LCD_Init();
	LCD_ShowNum(1, 1, unCurNum, 5);
	
	while(1)
	{
		uchCurKey = GetCurKey();
		if(uchCurKey == 1)
		{
			unCurNum++;
			LCD_ShowNum(1, 1, unCurNum, 5);
		}
		else if(uchCurKey == 2)
		{
			unCurNum--;
			LCD_ShowNum(1, 1, unCurNum, 5);
		}
		else if(uchCurKey == 3)
		{
			AT24C02_WriteByte(0, unCurNum % 256);
			AT24C02_WriteByte(1, unCurNum / 256);
			
			LCD_ShowString(2, 1, "Write ok");
			Delay(1000);
			LCD_ShowString(2, 1, "        ");
		}
		else if(uchCurKey == 4)
		{
			unCurNum = AT24C02_ReadByte(0);
			unCurNum += AT24C02_ReadByte(1) * 256;
			
			LCD_ShowNum(1, 1, unCurNum, 5);
			
			LCD_ShowString(2, 1, "Read ok");
			Delay(1000);
			LCD_ShowString(2, 1, "        ");
		}
		else {}
	};
	
	return 0;
}