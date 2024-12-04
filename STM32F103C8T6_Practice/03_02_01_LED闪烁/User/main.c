#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//使能GPIO时钟
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;				//设置输出模式为推挽输出
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_0;					
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;			
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);
	
	while(1)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);						//拉低电平
		Delay_ms(500);
		GPIO_SetBits(GPIOA, GPIO_Pin_0);						//拉高电平
		Delay_ms(500);
		
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);			//拉低电平
		Delay_ms(500);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);				//拉高电平
		Delay_ms(500);
		
		GPIO_Write(GPIOA, 0x00);								//拉低电平
		Delay_ms(500);
		GPIO_Write(GPIOA, 0x01);								//拉高电平
		Delay_ms(500);
	}
}
