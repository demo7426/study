/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	AD.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.17
描  述: AD模数转换
备  注:  
修改记录: 

  1.  日期: 2024.12.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "AD.h"


unsigned short g_usAD_Value[4] = { 0 };

/// @brief 初始化
/// @param 无
/// @return 无
void AD_Init(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	ADC_InitTypeDef tADC_InitTypeDef;
	DMA_InitTypeDef tDMA_InitTypeDef;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);									//设置模数转换分频为12MHz
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AIN;						//设置为模拟量输入
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_0;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);								//初始化GPIO
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);		//设置采样通道、数量、频率
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);		//设置采样通道、数量、频率
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);		//设置采样通道、数量、频率
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);		//设置采样通道、数量、频率
	
	tADC_InitTypeDef.ADC_Mode = ADC_Mode_Independent;					//工作在独立ADC模式，而非双ADC模式
	tADC_InitTypeDef.ADC_DataAlign = ADC_DataAlign_Right;				//采集到的数据，在寄存器存储时右对齐					
	tADC_InitTypeDef.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//使用软件触发
	tADC_InitTypeDef.ADC_ContinuousConvMode = DISABLE;					//不连续扫描
#ifdef AD_CONTI_TRANSFER
	tADC_InitTypeDef.ADC_ContinuousConvMode = ENABLE;					//连续扫描
#endif
	tADC_InitTypeDef.ADC_ScanConvMode = ENABLE;							//连续转换
	tADC_InitTypeDef.ADC_NbrOfChannel = 4; 								//指定扫描模式下，总共会用到几个通道
	ADC_Init(ADC1, &tADC_InitTypeDef); 
	
	tDMA_InitTypeDef.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
	tDMA_InitTypeDef.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	tDMA_InitTypeDef.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//DMA地址不自增
	tDMA_InitTypeDef.DMA_MemoryBaseAddr = (uint32_t)g_usAD_Value;
	tDMA_InitTypeDef.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	tDMA_InitTypeDef.DMA_MemoryInc = DMA_MemoryInc_Enable;				//DMA地址自增
	tDMA_InitTypeDef.DMA_DIR = DMA_DIR_PeripheralSRC;
	tDMA_InitTypeDef.DMA_BufferSize = 4;
	tDMA_InitTypeDef.DMA_Mode = DMA_Mode_Normal;						//传输计数器不自动重装
#ifdef AD_CONTI_TRANSFER
	tDMA_InitTypeDef.DMA_Mode = DMA_Mode_Circular;						//传输计数器自动重装
#endif
	tDMA_InitTypeDef.DMA_M2M = DMA_M2M_Disable;							//硬件触发DMA数据搬运
	tDMA_InitTypeDef.DMA_Priority = DMA_Priority_Medium;				//该通道DMA搬运数据的优先级
	
	DMA_Init(DMA1_Channel1, &tDMA_InitTypeDef);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_DMACmd(ADC1, ENABLE);											//使能ADC的DMA硬件触发信号
	ADC_Cmd(ADC1, ENABLE);												//开启AD转换
	
	ADC_ResetCalibration(ADC1);											//重置校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);					//等待重置校准完成
	ADC_StartCalibration(ADC1);											//开启自动校准
	while(ADC_GetCalibrationStatus(ADC1) == SET);						//等待开启自动校准完成
	
#ifdef AD_CONTI_TRANSFER
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);								//软件触发AD转换
#endif
}

#ifndef AD_CONTI_TRANSFER
void AD_GetValue(void)
{	
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, 4);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);								//软件触发AD转换
		
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET); 
	DMA_ClearFlag(DMA1_FLAG_TC1);
}
#endif
