/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MyCAN.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.28
描  述: CAN协议数据收发模块
备  注: 采用中断接收数据 
修改记录: 

  1.  日期: 2025.11.28
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <string.h>

#include "MyCAN.h"

static uint8_t g_uchMyCAN_ReceiveFlag = 0;
static CanRxMsg g_tCanRxMsg = { 0 };

void MyCAN_Init(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	CAN_InitTypeDef tCAN_InitTypeDef;
	CAN_FilterInitTypeDef tCAN_FilterInitTypeDef;
	
	NVIC_InitTypeDef tNVIC_InitTypeDef;
	
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
	
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	tNVIC_InitTypeDef.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	tNVIC_InitTypeDef.NVIC_IRQChannelCmd = ENABLE;
	tNVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority = 1;
	tNVIC_InitTypeDef.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&tNVIC_InitTypeDef);
	
	tCAN_InitTypeDef.CAN_Mode = CAN_Mode_Normal;
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
	return g_uchMyCAN_ReceiveFlag;
}

void MyCAN_Receive(CanRxMsg* _pCanRxMsg)
{
	*_pCanRxMsg = g_tCanRxMsg;
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
	if(CAN_GetITStatus(CAN1, CAN_IT_FMP0) == SET)
	{
		CAN_Receive(CAN1, CAN_FIFO0, &g_tCanRxMsg);			//内部会自动清除中断标志位
		g_uchMyCAN_ReceiveFlag = 1;
	}
}





