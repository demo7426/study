/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Buzzer.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.22
描  述: 蜂鸣器模块
备  注:  
修改记录: 

  1.  日期: 2024.11.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>
#include <INTRINS.h>

#include "Buzzer.h"

#define Buzzer_IO P2_5

static void Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}


void Buzzer_Time(unsigned int _Ms)
{
	int i =0;
	
	for(i = 0; i < _Ms * 2; ++i)			//1KMHZ提示音
	{
		Buzzer_IO = ~Buzzer_IO;
		Delay500us();					
	}
}	
