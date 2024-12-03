/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.01
描  述: 直流电机调速
备  注:  
修改记录: 

  1.  日期: 2024.12.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/
#include <REGX52.H>

#include "Key.h"
#include "Delay.h"
#include "NixieTube.h"
#include "Timer1.h"
#include "LCD1602.h"
#include "IR.h"

int main(void)
{
	unsigned int unCurSpeed = 0;					//速度
	unsigned char uchAddr = 0;						//地址
	unsigned char uchCommand = 0;					//命令
	
	Timer1_Init();
	IR_Init();
	
	SetNixieTube(1, unCurSpeed / 25);
	
	while(1)
	{		
		//红外信号命令判定
		if(IR_GetDataFlag() || IR_GetRepeatFlag())
		{
			uchAddr = IR_GetAddress();
			uchCommand = IR_GetCommand();
			
			if(uchCommand == IR_0)
				unCurSpeed = 0;
			if(uchCommand == IR_1)
				unCurSpeed = 25;
			if(uchCommand == IR_2)
				unCurSpeed = 50;
			if(uchCommand == IR_3)
				unCurSpeed = 75;
			if(uchCommand == IR_4)
				unCurSpeed = 100;
						
			Timer1_SetCurSpeed(unCurSpeed);	
		}
		SetNixieTube(1, unCurSpeed / 25);
	}
	
	return 0;
}
