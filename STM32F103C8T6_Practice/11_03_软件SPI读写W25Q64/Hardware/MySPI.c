/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MySPI.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.29
描  述: 软件模拟SPI总线
备  注:  
修改记录: 

  1.  日期: 2024.12.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "MySPI.h"

static void MySPI_W_SS(uint8_t _BitVal)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)_BitVal);
}

static void MySPI_W_SCK(uint8_t _BitVal)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)_BitVal);
}

static void MySPI_W_MOSI(uint8_t _BitVal)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)_BitVal);
}

static uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

void MySPI_Init(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//使能GPIO时钟
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;				//设置为推挽输出
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);						//初始化GPIO
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_IPU;				//设置为上拉输入
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_6;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);						//初始化GPIO
	
	//使用SPI模式0
	MySPI_W_SS(1);
	MySPI_W_SCK(0);
}

void MySPI_Start(void)
{
	MySPI_W_SS(0);
}

void MySPI_Stop(void)
{
	MySPI_W_SS(1);
}

uint8_t MySPI_SwapByte(uint8_t _Byte)
{
	uint8_t uchRet = 0;
	uint8_t i =0;
	
	for(i = 0; i < 8; ++i)
	{
		MySPI_W_MOSI(_Byte & (0x80 >>  i));
		MySPI_W_SCK(1);
		if(MySPI_R_MISO() == 1) { uchRet |= (0x80 >> i); }
		MySPI_W_SCK(0);
	}
		
	return uchRet;
}

