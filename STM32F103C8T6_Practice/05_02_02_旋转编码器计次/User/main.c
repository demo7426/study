/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.07
描  述: 实现旋转编码器计次
备  注:  
修改记录: 

  1.  日期: 2024.12.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Encoder.h"

int main(void)
{
	OLED_Init();
	Encoder_Init();
	
	OLED_ShowString(1, 1, "Num:");
	
	while(1)
	{
		OLED_ShowSignedNum(2, 1, Encoder_GetCurCount(), 5);
	}
}
