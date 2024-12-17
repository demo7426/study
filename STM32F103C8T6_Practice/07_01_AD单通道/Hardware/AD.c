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

/// @brief 初始化
/// @param 无
/// @return 无
void AD_Init(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	ADC_InitTypeDef tADC_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);									//设置模数转换分频为12MHz
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AIN;						//设置为模拟量输入
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_0;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);								//初始化GPIO
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);		//设置采样通道、数量、频率
	
	tADC_InitTypeDef.ADC_Mode = ADC_Mode_Independent;					//工作在独立ADC模式，而非双ADC模式
	tADC_InitTypeDef.ADC_DataAlign = ADC_DataAlign_Right;				//采集到的数据，在寄存器存储时右对齐					
	tADC_InitTypeDef.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//使用软件触发
	tADC_InitTypeDef.ADC_ContinuousConvMode = DISABLE;					//是否连续转换
	tADC_InitTypeDef.ADC_ScanConvMode = DISABLE;						//是否连续触发
	tADC_InitTypeDef.ADC_NbrOfChannel = 1; 								//指定扫描模式下，总共会用到几个通道
	ADC_Init(ADC1, &tADC_InitTypeDef); 
	
	ADC_Cmd(ADC1, ENABLE);												//开启AD转换
	
	ADC_ResetCalibration(ADC1);											//重置校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);					//等待重置校准完成
	ADC_StartCalibration(ADC1);											//开启自动校准
	while(ADC_GetCalibrationStatus(ADC1) == SET);						//等待开启自动校准完成
}

unsigned short AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);								//软件触发AD转换
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);				//等待AD转换完成
	return ADC_GetConversionValue(ADC1);								//获取AD转换后的值
}