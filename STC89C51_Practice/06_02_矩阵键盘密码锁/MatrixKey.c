/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Delay.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.11
描  述: 读取矩阵键盘输入模块
备  注:  
修改记录: 

  1.  日期: 2024.11.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "MatrixKey.h"
#include "Delay.h"

int GetCurMatrixKeyInput(void)
{
	int nCurKey = 0;			//当前被按下的键盘值
	
	P1 = 0xFF;
	P1_3 = 0;
	if(P1_7==0) { Delay(20); while(P1_7==0); Delay(20); nCurKey = 1; }
	if(P1_6==0) { Delay(20); while(P1_6==0); Delay(20); nCurKey = 5; }
	if(P1_5==0) { Delay(20); while(P1_5==0); Delay(20); nCurKey = 9; }
	if(P1_4==0) { Delay(20); while(P1_4==0); Delay(20); nCurKey = 13; }
		
	P1 = 0xFF;
	P1_2 = 0;
	if(P1_7==0) { Delay(20); while(P1_7==0); Delay(20); nCurKey = 2; }
	if(P1_6==0) { Delay(20); while(P1_6==0); Delay(20); nCurKey = 6; }
	if(P1_5==0) { Delay(20); while(P1_5==0); Delay(20); nCurKey = 10; }
	if(P1_4==0) { Delay(20); while(P1_4==0); Delay(20); nCurKey = 14; }
		
	P1 = 0xFF;
	P1_1 = 0;
	if(P1_7==0) { Delay(20); while(P1_7==0); Delay(20); nCurKey = 3; }
	if(P1_6==0) { Delay(20); while(P1_6==0); Delay(20); nCurKey = 7; }
	if(P1_5==0) { Delay(20); while(P1_5==0); Delay(20); nCurKey = 11; }
	if(P1_4==0) { Delay(20); while(P1_4==0); Delay(20); nCurKey = 15; }
		
	P1 = 0xFF;
	P1_0 = 0;
	if(P1_7==0) { Delay(20); while(P1_7==0); Delay(20); nCurKey = 4; }
	if(P1_6==0) { Delay(20); while(P1_6==0); Delay(20); nCurKey = 8; }
	if(P1_5==0) { Delay(20); while(P1_5==0); Delay(20); nCurKey = 12; }
	if(P1_4==0) { Delay(20); while(P1_4==0); Delay(20); nCurKey = 16; }
	
	return nCurKey;
}