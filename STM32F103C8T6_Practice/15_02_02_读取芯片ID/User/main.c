/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.05
描  述: 读取芯片ID
备  注:  
修改记录: 

  1.  日期: 2025.01.05
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"

int main(void)
{
	OLED_Init();
	
	OLED_ShowString(1, 1, "F_Size:");
	OLED_ShowHexNum(1, 8, *((__IO uint16_t*)0x1FFFF7E0), 4);

	
	OLED_ShowString(2, 1, "U_ID:");
	OLED_ShowHexNum(2, 6, *((__IO uint16_t*)0x1FFFF7E8), 4);
	OLED_ShowHexNum(2, 11, *((__IO uint16_t*)0x1FFFF7E8 + 0x2), 4);
	OLED_ShowHexNum(3, 1, *((__IO uint32_t*)0x1FFFF7E8 + 0x4), 8);
	OLED_ShowHexNum(4, 1, *((__IO uint32_t*)0x1FFFF7E8 + 0x8), 8);
	
	while(1)
	{
	}
}
