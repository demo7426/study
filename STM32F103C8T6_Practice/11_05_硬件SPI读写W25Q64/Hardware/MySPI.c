/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MySPI.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.30
描  述: 硬件模拟SPI总线
备  注:  
修改记录: 

  1.  日期: 2024.12.30
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

void MySPI_Init(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	SPI_InitTypeDef tSPI_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);		//使能SPI1时钟
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;				//设置为推挽输出
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_4;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);						//初始化GPIO
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;				//设置为复用推挽输出
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);						//初始化GPIO
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_IPU;				//设置为上拉输入
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_6;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);						//初始化GPIO
	
	tSPI_InitTypeDef.SPI_Mode = SPI_Mode_Master;							//设置为主机
	tSPI_InitTypeDef.SPI_Direction = SPI_Direction_2Lines_FullDuplex;		//SPI可收可发
	tSPI_InitTypeDef.SPI_DataSize = SPI_DataSize_8b;						//8位传输数据
	tSPI_InitTypeDef.SPI_FirstBit = SPI_FirstBit_MSB;						//设置数据高位先行
	tSPI_InitTypeDef.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;		//128分频			
	tSPI_InitTypeDef.SPI_CPOL = SPI_CPOL_Low;								//设置SPI主机通信模式
	tSPI_InitTypeDef.SPI_CPHA = SPI_CPHA_1Edge;								//设置SPI主机通信模式
	tSPI_InitTypeDef.SPI_NSS = SPI_NSS_Soft;								//软件控制片选SS信号
	tSPI_InitTypeDef.SPI_CRCPolynomial = 7;									//默认参数为7
	
	SPI_Init(SPI1, &tSPI_InitTypeDef);
	
	SPI_Cmd(SPI1, ENABLE);
	
	//使用SPI模式0
	MySPI_W_SS(1);
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
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);
	
	SPI_I2S_SendData(SPI1, _Byte);
	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET);
		
	return SPI_I2S_ReceiveData(SPI1);
}

