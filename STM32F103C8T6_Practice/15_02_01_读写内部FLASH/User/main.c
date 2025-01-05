/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.05
描  述: 读写内部FLASH
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
#include "Store.h"
#include "Key.h"
#include "MyFlash.h"

int main(void)
{
	int nCurIntKey = 0;
	
	OLED_Init();
	Key_Init();
	Store_Init();
	
	OLED_ShowString(1, 1, "Flag:");
	OLED_ShowString(2, 1, "Data:");
	
	while(1)
	{
		nCurIntKey = Key_GetCurKey();
		
		if(nCurIntKey == 1)
		{
			g_usStoreData[1]++;
			g_usStoreData[2]++;
			g_usStoreData[3]++;
			g_usStoreData[4]++;
			
			Store_Save();
		}
		else if(nCurIntKey == 2)
		{
			Store_Clear();
		}
		
		OLED_ShowHexNum(1, 6, g_usStoreData[0], 4);
		OLED_ShowHexNum(3, 1, g_usStoreData[1], 4);
		OLED_ShowHexNum(3, 6, g_usStoreData[2], 4);
		OLED_ShowHexNum(4, 1, g_usStoreData[3], 4);
		OLED_ShowHexNum(4, 6, g_usStoreData[4], 4);
	}
}
