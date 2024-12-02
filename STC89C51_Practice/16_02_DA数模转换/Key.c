/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Key.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.12
描  述: 独立按键模块
备  注:  
修改记录: 

  1.  日期: 2024.11.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "Key.h"
#include "Delay.h"

int g_nCurKey = 0;						//当前key值

static int GetKey(void)
{
	int nCurKey = 0;
	
	if(P3_1==0){ nCurKey = 1; } 
	if(P3_0==0){ nCurKey = 2; } 
	if(P3_2==0){ nCurKey = 3; } 
	if(P3_3==0){ nCurKey = 4; } 
		
	return nCurKey;
}

void KeyLoop(void)
{
	static int nLastKey = 0;
	static int nCurKey = 0;
	
	nCurKey = GetKey();
	if(nLastKey == 1 && nCurKey == 0) g_nCurKey = 1;
	if(nLastKey == 2 && nCurKey == 0) g_nCurKey = 2;
	if(nLastKey == 3 && nCurKey == 0) g_nCurKey = 3;
	if(nLastKey == 4 && nCurKey == 0) g_nCurKey = 4;
	
	nLastKey = nCurKey;
}

int GetCurKey(void)
{
	int nCurKey = g_nCurKey;
	
	g_nCurKey = 0;
	
	return nCurKey;
}