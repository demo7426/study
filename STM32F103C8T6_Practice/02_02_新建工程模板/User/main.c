#include "stm32f10x.h"                  // Device header

int main(void)
{
	/*
	RCC->APB2ENR = 0x00000010;										//使能GPIO 13端口
	GPIOC->CRH = 0x00300000;
	GPIOC->ODR = 0x00002000;										//GPIO 13端口模式配置
	//GPIOC->ODR = 0x00000000;										//设置GPIO 13端口电平
	*/
	
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);			//使能GPIO 13端口
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_13;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &tGPIO_InitTypeDef);							//GPIO 13端口模式配置
	
	//设置GPIO 13端口电平
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	//GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	
	while(1)
	{
		
	}
}
