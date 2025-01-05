/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Store.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.06
描  述: 内部Flash数据存储模块
备  注:  
修改记录: 

  1.  日期: 2025.01.06
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "Store.h"
#include "MyFlash.h"

#define FLASH_STARTADDR 0x0800FC00						//使用最后一页的程序存储器保存自定义数据

uint16_t g_usStoreData[512] = { 0 };					//保存在内部Flash中的数据

void Store_Init(void)
{
	int16_t i = 0;
	
	if(MyFlash_ReadHalfWord(FLASH_STARTADDR) != 0xA5A5)		//未初始化内存区域
	{
		MyFlash_ErasePage(FLASH_STARTADDR);
		
		MyFlash_ProgramHalfWord(FLASH_STARTADDR, 0xA5A5);
		
		for(i = 1; i < 512; i++)
		{
			MyFlash_ProgramHalfWord(FLASH_STARTADDR + i * 2, 0x0000);
		}
	}
	
	//读取之前保存在Flash中的数据
	for(i = 0; i < 512; i++)
	{
		g_usStoreData[i] = MyFlash_ReadHalfWord(FLASH_STARTADDR + i * 2);
	}
}

void Store_Save(void)
{
	int16_t i = 0;
	
	MyFlash_ErasePage(FLASH_STARTADDR);		
	
	for(i = 0; i < 512; i++)//保存已经初始化的标志,防止二次初始化错误判定
	{
		MyFlash_ProgramHalfWord(FLASH_STARTADDR + i * 2, g_usStoreData[i]);
	}
}

void Store_Clear(void)
{
	int16_t i = 0;
	
	for(i = 1; i < 512; i++)
		g_usStoreData[i] = 0;
	
	Store_Save();
}
