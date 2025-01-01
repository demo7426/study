/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.01
描  述: 读写备份寄存器
备  注:  
修改记录: 

  1.  日期: 2025.01.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Key.h"

int main(void)
{
	uint16_t usWriteArray[] = { 0x1234, 0x5678 };			//写入的数据
	uint16_t usReadArray[2] = { 0 };						//读出的数据
		
	OLED_Init();
	Key_Init();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);		//使能PWR时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);		//使能BKP时钟
		
	PWR_BackupAccessCmd(ENABLE);							//使能对BKP和RTC的访问
	
	OLED_ShowString(1, 1, "W:");
	OLED_ShowString(2, 1, "R:");
	
	BKP_WriteBackupRegister(BKP_DR1, usWriteArray[0]);
	BKP_WriteBackupRegister(BKP_DR2, usWriteArray[1]);
	
	while(1)
	{
		if(Key_GetCurKey() == 1)
		{
			usWriteArray[0]++;
			usWriteArray[1]++;
			
			BKP_WriteBackupRegister(BKP_DR1, usWriteArray[0]);
			BKP_WriteBackupRegister(BKP_DR2, usWriteArray[1]);
		}
		
		OLED_ShowHexNum(1, 3, usWriteArray[0], 4);
		OLED_ShowHexNum(1, 8, usWriteArray[1], 4);	
		OLED_ShowHexNum(2, 3, BKP_ReadBackupRegister(BKP_DR1), 4);
		OLED_ShowHexNum(2, 8, BKP_ReadBackupRegister(BKP_DR1), 4);		
	}
}
