/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	AT24C02.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.24
描  述: 对AT24C02内部读写数据模块
备  注:  
修改记录: 

  1.  日期: 2024.11.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/
#include <REGX52.H>

#include "I2C.h"

#define AT24C02_SLAVEADDR 0xA0			//AT24C02的硬件地址

static void Delay5ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 9;
	j = 244;
	do
	{
		while (--j);
	} while (--i);
}

void AT24C02_WriteByte(unsigned char _Addr, unsigned char _Data)
{
	I2C_Start();
	I2C_SendByte(AT24C02_SLAVEADDR);
	I2C_RecvAck();
	I2C_SendByte(_Addr);
	I2C_RecvAck();
	I2C_SendByte(_Data);
	I2C_RecvAck();
	I2C_Stop();
	
	Delay5ms();													//保证数据完全写入E²PROM
}

unsigned char AT24C02_ReadByte(unsigned char _Addr)
{
	unsigned char uchReadByte = 0;
	
	I2C_Start();
	I2C_SendByte(AT24C02_SLAVEADDR);
	I2C_RecvAck();
	I2C_SendByte(_Addr);
	I2C_RecvAck();
	I2C_Start();
	I2C_SendByte(AT24C02_SLAVEADDR | 0x01);
	I2C_RecvAck();
	uchReadByte = I2C_RecvByte();
	I2C_SendAck(1);
	I2C_Stop();
	
	return uchReadByte;
}
