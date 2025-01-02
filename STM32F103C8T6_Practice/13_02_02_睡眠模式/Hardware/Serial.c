/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Serial.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.22
描  述: 串口模块
备  注:  
修改记录: 

  1.  日期: 2024.12.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "Serial.h"

#include <stdarg.h>

unsigned char g_uchRxData = 0;
unsigned char g_uchRxFlag = 0;

/// @brief 求次方
/// @param _Num--底数
/// @param _Pow--幂
/// @return 最终的次方值
static unsigned int Serial_Pow(unsigned int _Num, unsigned int _Pow)
{
	unsigned int unRes = 1;
	
	while(_Pow--)
		unRes *= _Num;

	return unRes;
}

void Serial_Init(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	USART_InitTypeDef tUSART_InitTypeDef;
	NVIC_InitTypeDef tNVIC_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;										//复用推挽输出的端口
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_9;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_IPU;										
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_10;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);
	
	tUSART_InitTypeDef.USART_BaudRate = 9600;											//波特率
	tUSART_InitTypeDef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//不使用串口的硬件流控
	tUSART_InitTypeDef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	tUSART_InitTypeDef.USART_Parity = USART_Parity_No;									//不启用奇偶校验
	tUSART_InitTypeDef.USART_StopBits = USART_StopBits_1;								//停止位为1位
	tUSART_InitTypeDef.USART_WordLength = USART_WordLength_8b;							//数据位
	
	USART_Init(USART1, &tUSART_InitTypeDef);											//配置串口参数
	
	//使能中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	tNVIC_InitTypeDef.NVIC_IRQChannel = USART1_IRQn;
	tNVIC_InitTypeDef.NVIC_IRQChannelCmd = ENABLE;
	tNVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority = 1;
	tNVIC_InitTypeDef.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&tNVIC_InitTypeDef);
	
	USART_Cmd(USART1, ENABLE);															//启动串口
}

void Serial_SendByte(unsigned char _Byte)
{
	USART_SendData(USART1, _Byte);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(unsigned char* _pAddr, unsigned short _Size)
{
	unsigned short i = 0;
	
	for(i = 0; i < _Size; ++i)
	{
		Serial_SendByte(_pAddr[i]);
	}
}

void Serial_SendString(char* _Content)
{
	unsigned int i = 0;
	
	for(i = 0; _Content[i] != '\0'; ++i)
	{
		Serial_SendByte(_Content[i]);
	}
}

 

void Serial_SendNumber(unsigned int _Number, unsigned char _NumLen)
{
	unsigned short i = 0;
	
	for(i = 0; i < _NumLen; ++i)
	{
		Serial_SendByte(_Number / (Serial_Pow(10, _NumLen - i - 1)) % 10 + '0');
	}
}

void Serial_Printf(char* format, ...)
{
	char chContext[128] = { 0 };
	
	va_list arg;
	va_start(arg, format);
	vsprintf(chContext, format, arg);
	va_end(arg);
	
	Serial_SendString(chContext);
}

unsigned char Serial_GetRxFlag(void)
{
	if(g_uchRxFlag == 1)
	{
		g_uchRxFlag = 0;
		return 1;
	}
	
	return 0;
}

unsigned char Serial_GetRxData(void)
{
	return g_uchRxData;
}

//覆盖printf函数的底层实现，让其输出到串口中去
int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}


void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	{
		g_uchRxData = USART_ReceiveData(USART1);
		g_uchRxFlag = 1;
	}
}

