/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.03
描  述: 红外遥控
备  注:  
修改记录: 

  1.  日期: 2024.12.03
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "LCD1602.h"
#include "IR.h"

int main(void)
{
	unsigned char uchAddr = 0;				//地址
	unsigned char uchCommand = 0;			//命令
	unsigned char uchNum = 0;
	
	LCD_Init();
	IR_Init();
	
	LCD_ShowString(1, 1, "Addr Com Num");
	LCD_ShowString(2, 1, "00   00  000");
	
	while(1)
	{
		if(IR_GetDataFlag() || IR_GetRepeatFlag())
		{
			uchAddr = IR_GetAddress();
			uchCommand = IR_GetCommand();
			
			LCD_ShowHexNum(2, 1, uchAddr, 2);
			LCD_ShowHexNum(2, 6, uchCommand, 2);
			
			if(uchCommand == IR_VOL_ADD)
				uchNum++;
			else if(uchCommand == IR_VOL_MINUS)
				uchNum--;
			
			LCD_ShowNum(2, 10, uchNum, 3);
		}
	}
}
