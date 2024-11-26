/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	I2C.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.24
描  述: I2C模块
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

#define I2C_SCL P2_1				
#define I2C_SDA P2_0

void I2C_Start(void)
{
	I2C_SDA = 1;
	I2C_SCL = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
}

void I2C_Stop(void)
{
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
}

void I2C_SendByte(unsigned char _Data)
{
	unsigned char i = 0;
	
	for(i = 0; i < 8; ++i)
	{
		I2C_SDA = _Data & (0x80 >> i);		//高位优先发送
		I2C_SCL = 1;						
		I2C_SCL = 0;											//AT89C52时钟较小，变化速率较慢，故AT89C02可以识别到波形变化
	}
}

unsigned char I2C_RecvByte(void)
{
	unsigned char i = 0;
	unsigned char uchReadByte = 0;
	
	I2C_SDA = 1;
	
	for(i = 0; i < 8; ++i)
	{		
		I2C_SCL = 1;		
		if(I2C_SDA)
			uchReadByte |= (0x80 >> i);
		I2C_SCL = 0;											//AT89C52时钟较小，变化速率较慢，故AT89C02可以识别到波形变化	
	}
	
	return uchReadByte;
}

void I2C_SendAck(unsigned char _Ack)
{
	I2C_SDA = _Ack;
	I2C_SCL = 1;
	I2C_SCL = 0;
}

unsigned char I2C_RecvAck(void)
{
	unsigned char uchAck = 0;
	
	I2C_SDA = 1;
	I2C_SCL = 1;
	uchAck = I2C_SDA;
	I2C_SCL = 0;
	
	return uchAck;
}
