#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//使能GPIO时钟
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;				//设置输出模式为推挽输出
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_All;					
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;			
	
	GPIO_Init(GPIOA, &tGPIO_InitTypeDef);
	
	while(1)
	{
		GPIO_Write(GPIOA, ~0x0001);								//拉低电平
		Delay_ms(200);
		GPIO_Write(GPIOA, ~0x0002);								//拉低电平
		Delay_ms(200);
		GPIO_Write(GPIOA, ~0x0004);								//拉低电平
		Delay_ms(200);
		GPIO_Write(GPIOA, ~0x0008);								//拉低电平
		Delay_ms(200);
		GPIO_Write(GPIOA, ~0x0010);								//拉低电平
		Delay_ms(200);
		GPIO_Write(GPIOA, ~0x0020);								//拉低电平
		Delay_ms(200);
		GPIO_Write(GPIOA, ~0x0040);								//拉低电平
		Delay_ms(200);
		GPIO_Write(GPIOA, ~0x0080);								//拉低电平
		Delay_ms(200);
		
	}
}
