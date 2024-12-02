/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	XPT2046.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.02
描  述: XPT2046数据模块
备  注:  
修改记录: 

  1.  日期: 2024.12.02
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "XPT2046.h"

#define XPT2046_CS 		P3_5
#define XPT2046_DCLK	P3_6
#define XPT2046_DIN		P3_4
#define XPT2046_DOUT 	P3_7

unsigned int XPT2046_ReadCurAD(unsigned char _Command)
{
	int i = 0;
	unsigned int unReadAD = 0;
	
	XPT2046_CS = 0;
	
	for(i = 0; i < 8; i++)
	{
		XPT2046_DIN = (_Command & (0x80 >> i));
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
	}
	
	for(i = 0; i < 16; i++)
	{
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
		if(XPT2046_DOUT) unReadAD |= (0x8000 >> i);
	}
	
	XPT2046_CS = 1;
	
	if(_Command & 0x80)
		unReadAD = unReadAD >> 8;
	else
		unReadAD = unReadAD >> 4;
	
	return unReadAD;
}
