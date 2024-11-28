/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	DS18B20.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.28
描  述: 温度读取模块
备  注:  
修改记录: 

  1.  日期: 2024.11.28
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "DS18B20.h"
#include "OneWire.h"

#define DS18B20_SKIPROM 		0xCC
#define DS18B20_CONVERT 		0x44
#define DS18B20_SCRATCHPAD 	0xBE

void DS18B20_Convert(void)
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIPROM);
	OneWire_SendByte(DS18B20_CONVERT);
}

float DS18B20_GetCurTemp(void)
{
	unsigned char uchLow, uchHigh;
	int nTemp = 0;
	float fTemp = 0;
	
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIPROM);
	OneWire_SendByte(DS18B20_SCRATCHPAD);
	
	uchLow = OneWire_RecvByte();
	uchHigh = OneWire_RecvByte();
	nTemp = uchHigh << 8 | uchLow;
	fTemp = nTemp / 16.0;
	
	return fTemp;
}

