/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MyDMA.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.20
描  述: DMA数据转运模块
备  注: stm32f103c8t6只有一个DMA（7个通道）
修改记录: 

  1.  日期: 2024.12.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "MyDMA.h"

static unsigned int g_unCount = 0;

void MyDMA_Init(unsigned int _SrcAddr, unsigned int _DesAddr, unsigned int _Count)
{
	DMA_InitTypeDef tDMA_InitTypeDef;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	tDMA_InitTypeDef.DMA_PeripheralBaseAddr = _SrcAddr;
	tDMA_InitTypeDef.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	tDMA_InitTypeDef.DMA_PeripheralInc = DMA_PeripheralInc_Enable;		//DMA地址自增
	tDMA_InitTypeDef.DMA_MemoryBaseAddr = _DesAddr;
	tDMA_InitTypeDef.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	tDMA_InitTypeDef.DMA_MemoryInc = DMA_MemoryInc_Enable;				//DMA地址自增
	tDMA_InitTypeDef.DMA_DIR = DMA_DIR_PeripheralSRC;
	tDMA_InitTypeDef.DMA_BufferSize = _Count;
	tDMA_InitTypeDef.DMA_Mode = DMA_Mode_Normal;						//传输计数器不自动重装
	tDMA_InitTypeDef.DMA_M2M = DMA_M2M_Enable;							//软件触发DMA数据搬运
	tDMA_InitTypeDef.DMA_Priority = DMA_Priority_Medium;				//该通道DMA搬运数据的优先级
	
	DMA_Init(DMA1_Channel1, &tDMA_InitTypeDef);
	
	DMA_Cmd(DMA1_Channel1, DISABLE);
	
	g_unCount = _Count;
}

void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, g_unCount);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET); 
	DMA_ClearFlag(DMA1_FLAG_TC1);
}

