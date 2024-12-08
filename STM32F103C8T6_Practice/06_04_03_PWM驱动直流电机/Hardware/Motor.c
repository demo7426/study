/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Motor.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.08
描  述: 直流电机驱动模块
备  注:  
修改记录: 

  1.  日期: 2024.12.08
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "PWM.h"

void Motor_Init(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//使能GPIO时钟
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;				//设置为推挽输出
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);						//初始化GPIO
	
	PWM_Init();
}

/// @brief 设置当前速度
/// @param _Speed--速度;值:0~100
/// @return 无
void Servo_SetCurSpeed(int _Speed)
{
	if(_Speed >= 0)
	{
		//控制直流电机旋转方向
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		
		PWM_SetCompare3(_Speed);
	}
	else
	{
		//控制直流电机旋转方向
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		
		PWM_SetCompare3(-_Speed);	
	}
}

