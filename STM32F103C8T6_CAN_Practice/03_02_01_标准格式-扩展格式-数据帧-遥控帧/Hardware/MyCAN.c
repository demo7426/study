/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MyCAN.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.25
描  述: CAN协议数据收发模块
备  注:  
修改记录: 

  1.  日期: 2025.11.25
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <string.h>

#include "MyCAN.h"

void MyCAN_Init(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	CAN_InitTypeDef tCAN_InitTypeDef;
	CAN_FilterInitTypeDef tCAN_FilterInitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;				//复用推挽输出
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_12;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);									//初始化GPIO
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_IPU;					//复用上拉输出
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_11;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);									//初始化GPIO
	
	tCAN_InitTypeDef.CAN_Mode = CAN_Mode_LoopBack;
	tCAN_InitTypeDef.CAN_Prescaler = 48;									//预分频;波特率 = 36MHz / 48 / (1 + 2 + 3) = 125KHz
	tCAN_InitTypeDef.CAN_BS1 = CAN_BS1_2tq;	
	tCAN_InitTypeDef.CAN_BS2 = CAN_BS2_3tq;
	tCAN_InitTypeDef.CAN_SJW = CAN_SJW_2tq;
	tCAN_InitTypeDef.CAN_NART = DISABLE;
	tCAN_InitTypeDef.CAN_TXFP = DISABLE;
	tCAN_InitTypeDef.CAN_RFLM = DISABLE;
	tCAN_InitTypeDef.CAN_AWUM = DISABLE;
	tCAN_InitTypeDef.CAN_TTCM = DISABLE;
	tCAN_InitTypeDef.CAN_ABOM = DISABLE;
	CAN_Init(CAN1, &tCAN_InitTypeDef);										//初始化CAN收发器
	
	tCAN_FilterInitTypeDef.CAN_FilterNumber = 0;
	tCAN_FilterInitTypeDef.CAN_FilterIdHigh = 0x0000;
	tCAN_FilterInitTypeDef.CAN_FilterIdLow = 0x0000;
	tCAN_FilterInitTypeDef.CAN_FilterMaskIdHigh = 0x0000;
	tCAN_FilterInitTypeDef.CAN_FilterMaskIdLow = 0x0000;
	tCAN_FilterInitTypeDef.CAN_FilterScale = CAN_FilterScale_32bit;
	tCAN_FilterInitTypeDef.CAN_FilterMode = CAN_FilterMode_IdMask;
	tCAN_FilterInitTypeDef.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	tCAN_FilterInitTypeDef.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&tCAN_FilterInitTypeDef);							//初始化CAN过滤器
}

void MyCAN_Transmit(CanTxMsg* _pCanTxMsg)
{
	CAN_Transmit(CAN1, _pCanTxMsg);
}

uint8_t MyCAN_ReceiveFlag(void)
{
	if(CAN_MessagePending(CAN1, CAN_FIFO0) > 0)
		return 1;
	
	return 0;
}

void MyCAN_Receive(CanRxMsg* _pCanRxMsg)
{
	CAN_Receive(CAN1, CAN_FIFO0, _pCanRxMsg);
}







