/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Buzzer.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.26
描  述: 秒表(定时器扫描按键数码管)
备  注:  
修改记录: 

  1.  日期: 2024.11.26
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/
#include <REGX52.H>

#include "AT24C02.h"
#include "Key.h"
#include "Delay.h"
#include "NixieTube.h"
#include "Timer0.h"

static unsigned int g_unMin = 0;				//分
static unsigned int g_unSec = 0;				//秒
static unsigned int g_unMinSec = 0;			//百分之一秒
static int g_nIsStartSecWatch = 0;							//是否启动计时器;1--启动;0--不启动

int main(void)
{
	int nCurKey = 0;
	
	Timer0_Init();
	
	while(1)
	{
		SetNixieTube(1, g_unMin / 10);
		SetNixieTube(2, g_unMin % 10);
		SetNixieTube(3, 10);
		SetNixieTube(4, g_unSec / 10);
		SetNixieTube(5, g_unSec % 10);
		SetNixieTube(6, 10);
		SetNixieTube(7, g_unMinSec / 10);
		SetNixieTube(8, g_unMinSec % 10);
		
		nCurKey = GetCurKey();
		if(nCurKey == 0)
			continue;
		
		if(nCurKey == 1)
		{
			g_nIsStartSecWatch = !g_nIsStartSecWatch;
		}
		else if(nCurKey == 2)
		{
			g_unMin = 0;
			g_unSec = 0;
			g_unMinSec = 0;
		}
		else if(nCurKey == 3)
		{
			AT24C02_WriteByte(0, g_unMin);
			AT24C02_WriteByte(1, g_unSec);
			AT24C02_WriteByte(2, g_unMinSec);
		}
		else if(nCurKey == 4)
		{
			g_unMin = AT24C02_ReadByte(0);
			g_unSec = AT24C02_ReadByte(1);
			g_unMinSec = AT24C02_ReadByte(2);
		}
	}
	
	return 0;
}

void Timer0_Rountime(void) interrupt 1
{
	static unsigned int unSecWatchCount = 0;			//秒表计数
	static unsigned int unKeyCount = 0;						//独立按键计数
	static unsigned int unNixieTubeCount = 0;			//数码管计数
	
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	
	unSecWatchCount++;
	unKeyCount++;
	unNixieTubeCount++;
	
	if(unSecWatchCount >= 10)
	{
		unSecWatchCount = 0;
		
		if(g_nIsStartSecWatch)		//刷新计时器
		{
			g_unMinSec++;
			if(g_unMinSec >= 100)
			{
				g_unMinSec = 0;
				g_unSec++;
				if(g_unSec >= 60)
				{
					g_unSec = 0;
					g_unMin++;
					if(g_unMin >= 60)
						g_unMin = 0;
				}
			}
		}
	}
	
	if(unKeyCount >= 20)
	{
		unKeyCount = 0;
		
		KeyLoop();
	}
		
	if(unNixieTubeCount >= 2)
	{
		unNixieTubeCount = 0;
		
		NixieTubeLoop();
	}
	
	
}
