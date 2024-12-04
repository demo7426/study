#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//使能GPIO时钟
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;				//设置输出模式为推挽输出
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_12;					
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;			
	
	GPIO_Init(GPIOB, &tGPIO_InitTypeDef);
	
	while(1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);						//拉低电平
		Delay_ms(100);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);						//拉高电平
		Delay_ms(100);
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);						//拉低电平
		Delay_ms(100);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);						//拉高电平
		Delay_ms(700);		
	}
}
