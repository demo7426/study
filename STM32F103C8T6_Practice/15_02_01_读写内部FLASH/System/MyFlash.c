/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MyFlash.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.06
描  述: 内部Flash读写模块
备  注:  
修改记录: 

  1.  日期: 2025.01.06
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "MyFlash.h"

uint32_t MyFlash_ReadWord(uint32_t _Addr)
{
	return *((__IO uint32_t*)_Addr);
}

uint16_t MyFlash_ReadHalfWord(uint32_t _Addr)
{
	return *((__IO uint16_t*)_Addr);
}

uint8_t MyFlash_ReadByte(uint32_t _Addr)
{
	return *((__IO uint8_t*)_Addr);
}

void MyFlash_EraseAllPages(void)
{
	FLASH_Unlock();
	FLASH_EraseAllPages();
	FLASH_Lock();
}

void MyFlash_ErasePage(uint32_t _Addr)
{
	FLASH_Unlock();
	FLASH_ErasePage(_Addr);
	FLASH_Lock();
}

void MyFlash_ProgramWord(uint32_t _Addr, uint32_t _Data)
{
	FLASH_Unlock();
	FLASH_ProgramWord(_Addr, _Data);
	FLASH_Lock();
}

void MyFlash_ProgramHalfWord(uint32_t _Addr, uint16_t _Data)
{
	FLASH_Unlock();
	FLASH_ProgramHalfWord(_Addr, _Data);
	FLASH_Lock();
}




