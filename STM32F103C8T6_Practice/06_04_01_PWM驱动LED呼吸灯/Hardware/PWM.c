/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	PWM.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.08
描  述: PWM模块
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

void PWM_Init(void)
{
#if 1		//使用默认复用GPIO的PA0端口
	
	TIM_TimeBaseInitTypeDef tTIM_TimeBaseInitTypeDef;
	TIM_OCInitTypeDef tTIM_OCInitTypeDef;
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);				
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;					//设置为复用推挽输出，由外部设备控制该IO
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_0;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//使能定时器2的时钟
	
	TIM_InternalClockConfig(TIM2);									//选择使用内部时钟
	
	tTIM_TimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;		//不分频
	tTIM_TimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;	//设置计数器模式:向上计数
	
	//定时器重装值（定时频率=72MHz/(PSC+1)/(ARR+1)）（定时频率=72MHz/(99+1)/(719+1)）
	tTIM_TimeBaseInitTypeDef.TIM_Period = 100 - 1;				
	tTIM_TimeBaseInitTypeDef.TIM_Prescaler = 720 - 1;				//定时器预分频器
	tTIM_TimeBaseInitTypeDef.TIM_RepetitionCounter = 0;				//重复计数器的值
	
	TIM_TimeBaseInit(TIM2, &tTIM_TimeBaseInitTypeDef);				//设置时基单元
	
	//清除上一步设置时基单元时，TIMx->EGR = TIM_PSCReloadMode_Immediate; 启动的更新标志位
	//保证定时器从最开始不会被触发
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);							
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);						//中断输出控制
	
	//配置定时器比较器部分
	tTIM_OCInitTypeDef.TIM_OCMode = TIM_OCMode_PWM1;
	tTIM_OCInitTypeDef.TIM_OCPolarity = TIM_OCPolarity_High;
	tTIM_OCInitTypeDef.TIM_OutputState = TIM_OutputState_Enable;
	tTIM_OCInitTypeDef.TIM_Pulse = 0;
	
	TIM_OC1Init(TIM2, &tTIM_OCInitTypeDef);							//初始化第1个通道，该通道输出默认复用GPIO的PA0端口
	
	TIM_Cmd(TIM2, ENABLE);											//启动定时器

#else 			//Tim2的输出引脚从GPIO PA0重映射到GPIO PA15

	TIM_TimeBaseInitTypeDef tTIM_TimeBaseInitTypeDef;
	TIM_OCInitTypeDef tTIM_OCInitTypeDef;
	GPIO_InitTypeDef tGPIO_InitTypeDef;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);			//将Tim2的输出引脚从GPIO PA0重映射到GPIO PA15
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);		//关闭 GPIO PA15 默认的 JTAG 调试功能
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		 		
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;					//设置为复用推挽输出，由外部设备控制该IO
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_15;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//使能定时器2的时钟
	
	TIM_InternalClockConfig(TIM2);									//选择使用内部时钟
	
	tTIM_TimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;		//不分频
	tTIM_TimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;	//设置计数器模式:向上计数
	
	//定时器重装值（定时频率=72MHz/(PSC+1)/(ARR+1)）（定时频率=72MHz/(99+1)/(719+1)）
	tTIM_TimeBaseInitTypeDef.TIM_Period = 100 - 1;				
	tTIM_TimeBaseInitTypeDef.TIM_Prescaler = 720 - 1;				//定时器预分频器
	tTIM_TimeBaseInitTypeDef.TIM_RepetitionCounter = 0;				//重复计数器的值
	
	TIM_TimeBaseInit(TIM2, &tTIM_TimeBaseInitTypeDef);				//设置时基单元
	
	//清除上一步设置时基单元时，TIMx->EGR = TIM_PSCReloadMode_Immediate; 启动的更新标志位
	//保证定时器从最开始不会被触发
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);							
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);						//中断输出控制
	
	//配置定时器比较器部分
	TIM_OCStructInit(&tTIM_OCInitTypeDef);
	tTIM_OCInitTypeDef.TIM_OCMode = TIM_OCMode_PWM1;
	tTIM_OCInitTypeDef.TIM_OCPolarity = TIM_OCPolarity_High;
	tTIM_OCInitTypeDef.TIM_OutputState = TIM_OutputState_Enable;
	tTIM_OCInitTypeDef.TIM_Pulse = 0;
	
	TIM_OC1Init(TIM2, &tTIM_OCInitTypeDef);							//初始化第1个通道，该通道输出默认复用GPIO的PA0端口
	
	TIM_Cmd(TIM2, ENABLE);											//启动定时器
#endif
}


void PWM_SetCompare1(unsigned int _Compare)
{
	TIM_SetCompare1(TIM2, _Compare);
}



