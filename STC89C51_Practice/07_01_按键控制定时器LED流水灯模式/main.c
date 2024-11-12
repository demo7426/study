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
#include <INTRINS.H>

#include "Timer0.h"
#include "Key.h"

static int g_nLEDMode = 0;			//0--右移(显示器效果左移);1--左移(显示器效果右移)

int main(void)
{
	int nCurKey = 0;
	P2 = 0xFE;
	
	Timer0_Init();
	
	while(1)
	{
		nCurKey = GetCurKey();
		if(nCurKey == 1)
			g_nLEDMode = 0;
		else if(nCurKey == 2)
			g_nLEDMode = 1;
		else {}
	}
	
	return 0;
}

void Timer0_Rountime(void) interrupt 1
{
	static int nCount = 0;
	
	nCount++;
	
	TL0 = 0x18;			//设置定时初值
	TH0 = 0xD1;			//设置定时初值
	
	if(nCount >= 500)
	{
		nCount = 0;
		
		if(g_nLEDMode == 0)
			P2 = _cror_(P2, 1);
		else
			P2 = _crol_(P2, 1);
	}
}
