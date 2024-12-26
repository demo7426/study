/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MyI2C.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.26
描  述: I2C协议模块
备  注:  
修改记录: 

  1.  日期: 2024.12.26
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "MyI2C.h"
#include "Delay.h"

#define MYI2C_GPIO 			GPIOB
#define MYI2C_Periph_GPIO 	RCC_APB2Periph_GPIOB
#define MYI2C_SCL 			GPIO_Pin_10
#define MYI2C_SDA 			GPIO_Pin_11

static void MyI2C_SCL_W(uint16_t _Data)
{
	GPIO_WriteBit(MYI2C_GPIO, MYI2C_SCL, (BitAction)_Data);
	Delay_us(10);
}

static void MyI2C_SDA_W(uint16_t _Data)
{
	GPIO_WriteBit(MYI2C_GPIO, MYI2C_SDA, (BitAction)_Data);
	Delay_us(10);
}

static uint8_t MyI2C_SDA_R(void)
{
	uint8_t uchBitValue = 0;
	
	uchBitValue = GPIO_ReadInputDataBit(MYI2C_GPIO, MYI2C_SDA);
	Delay_us(10);
	
	return uchBitValue;
}

void MyI2C_Init(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(MYI2C_Periph_GPIO, ENABLE);					//使能GPIO时钟
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_OD;						//设置为开漏输出
	tGPIO_InitTypeDef.GPIO_Pin = MYI2C_SDA |MYI2C_SCL;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(MYI2C_GPIO, &tGPIO_InitTypeDef);							//初始化GPIO
	
	GPIO_SetBits(MYI2C_GPIO, MYI2C_SDA |MYI2C_SCL);
}

void MyI2C_Start(void)
{
	MyI2C_SDA_W(1);
	MyI2C_SCL_W(1);
	MyI2C_SDA_W(0);
	MyI2C_SCL_W(0);
}

void MyI2C_Stop(void)
{
	MyI2C_SDA_W(0);
	MyI2C_SCL_W(1);
	MyI2C_SDA_W(1);
}

void MyI2C_SendByte(uint8_t _Byte)
{
	int8_t i = 0;
	
	for(i = 0; i < 8; ++i)
	{
		MyI2C_SDA_W(_Byte & (0x80 >> i));	//I2C协议高位先行
		MyI2C_SCL_W(1);
		MyI2C_SCL_W(0);
	}
}

uint8_t MyI2C_RecvByte(void)
{
	uint8_t uchByte = 0;
	int8_t i = 0;
	
	MyI2C_SDA_W(1);					//释放SDA线
	for(i = 7; i >= 0; --i)
	{
		MyI2C_SCL_W(1);
		uchByte |= (MyI2C_SDA_R() << i);
		MyI2C_SCL_W(0);
	}
	return uchByte;
}

void MyI2C_SendAck(uint8_t _Ack)
{
	MyI2C_SDA_W(_Ack);
	MyI2C_SCL_W(1);
	MyI2C_SCL_W(0);
}

uint8_t MyI2C_RecvAck(void)
{
	uint8_t uchAck = 0;
	
	MyI2C_SDA_W(1);
	
	MyI2C_SCL_W(1);
	uchAck = MyI2C_SDA_R();
	MyI2C_SCL_W(0);
	
	return uchAck;
}



