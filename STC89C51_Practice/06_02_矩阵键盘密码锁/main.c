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

#include "LCD1602.h"

int main(void)
{
	int nCurKey = 0;											//矩阵键盘当前输入键值
	
	int nCount = 0;												//按键输入次数
	int nPassword = 0;										//当前计算出的密码
	const int nDefaultPassword = 2345;		//验证密码
	
	LCD_Init();
	
	LCD_ShowString(1, 1, "Password:");
	
	while(1)
	{
		nCurKey = GetCurMatrixKeyInput();
		if(nCurKey <= 0 || nCurKey >= 13)
			continue;
		
		if(nCurKey > 0 && nCurKey < 10 && nCount < 4)
		{
			nPassword*=10;
			nPassword+=(nCurKey%10);
			
			nCount++;
			LCD_ShowNum(2, 1, nPassword, 4);
			continue;
		}
		
		if(nCurKey == 11)   	//确认按钮
		{
			if(nPassword == nDefaultPassword)
				LCD_ShowString(1, 14, "OK ");
			else
				LCD_ShowString(1, 14, "ERR");
			
			nPassword = 0; 
			nCount=0;
			LCD_ShowNum(2, 1, nPassword, 4);
		}
		else if(nCurKey == 12)			//取消按钮
		{
			nPassword = 0; 
			nCount=0;
			LCD_ShowNum(2, 1, nPassword, 4);
			LCD_ShowString(1, 14, "   ");
		}
		else{}
	}
	
	return 0;
}
