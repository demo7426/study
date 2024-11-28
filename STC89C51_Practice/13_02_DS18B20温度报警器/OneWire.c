/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	OneWire.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.29
描  述: 单总线模块
备  注: 在单总线操作时，需要关闭中断，防止中断影响到单总线的时序 
修改记录: 

  1.  日期: 2024.11.29
      作者: 钱锐
          1) 此为模板第一个版本;
      内容:
      版本:V0.1.0

*************************************************/
#include <REGX52.H>

#include "OneWire.h"
#include "LCD1602.h"

#define ONEWIRE_IO P3_7			//单总线I/O控制口

/// @brief 发送bit数据
/// @param _Bit--单bit数据
/// @return 无
static void OneWire_SendBit(unsigned char _Bit)
{
	unsigned char i;
	ET0 = 0;					//关闭中断，防止中断影响到单总线的时序
	ONEWIRE_IO = 0;
	
	//延时10us
	i = 2;
	while (--i);
	
	ONEWIRE_IO = _Bit;
	
	//延时50us
	i = 20;
	while (--i);
	
	ONEWIRE_IO = 1;
	ET0 = 1;
}

/// @brief 接收bit数据
/// @param 无
/// @return 接收的bit数据
static unsigned char OneWire_RecvBit(void)
{
	unsigned char uchBit = 0;
	
	unsigned char i;
	ET0 = 0;
	ONEWIRE_IO = 0;
	
	//延时5us
	i = 2;
	while (--i);
	
	ONEWIRE_IO = 1;
	
	//延时5us
	i = 2;
	while (--i);
	uchBit = ONEWIRE_IO;
	
	//延时50us
	i = 24;
	while (--i);
	ET0 = 1;
	return uchBit;
}


/// @brief 单总线初始化
/// @param 无
/// @return 无
void OneWire_Init(void)
{
	unsigned char i;
	ET0 = 0;
	ONEWIRE_IO = 1;
	ONEWIRE_IO = 0;

	//延时500us
	i = 227;
	while (--i);
	
	ONEWIRE_IO = 1;
	
	//延时80us
	i = 34;
	while (--i);
	
	//延时500us
	i = 227;
	while (--i);
	ET0 = 1;
}

void OneWire_SendByte(unsigned char _Byte)
{
	unsigned char i = 0;
	
	ET0 = 0;
	for(i = 0; i < 8; ++i)
	{
			OneWire_SendBit(_Byte & (0x01 << i));
	}
	ET0 = 1;
}

unsigned char OneWire_RecvByte(void)
{
	unsigned char i = 0;
	unsigned char uchByte = 0;
	
	ET0 = 0;
	for(i = 0; i < 8; ++i)
	{
			if(OneWire_RecvBit())
			{
				uchByte |= (0x01 << i);
			}
	}
	ET0 = 1;
	return uchByte;
}


