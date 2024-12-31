/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	W25Q64.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.29
描  述: 擦除、读写W25Q64 nor flash芯片
备  注:  
修改记录: 

  1.  日期: 2024.12.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "W25Q64.h"
#include "MySPI.h"
#include "W25Q64_Ins.h"

/// @brief flash写使能
/// @param 无
/// @return 无
static void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);	
	MySPI_Stop();
}

/// @brief 等待flash写结束
/// @param 无
/// @return 无
static void W25Q64_WaitBusy(void)
{
	uint32_t unTimeOut = 100000;
	
	MySPI_Start();
	
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)
	{
		unTimeOut--;
		if(unTimeOut <= 0)
			break;
	}
	
	MySPI_Stop();
}


void W25Q64_Init(void)
{
	MySPI_Init();
}

void W25Q64_ReadID(uint8_t* _pMID, uint16_t* _pDID)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_JEDEC_ID);
	
	*_pMID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*_pDID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*_pDID <<= 8;
	*_pDID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	
	MySPI_Stop();
}

void W25Q64_PageProgram(uint32_t _Addr, uint8_t* _pDataArray, uint16_t _Count)
{
	uint16_t i = 0;
	
	W25Q64_WriteEnable();
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MySPI_SwapByte(_Addr >> 16);
	MySPI_SwapByte(_Addr >> 8);
	MySPI_SwapByte(_Addr);
	
	for(i = 0; i < _Count; ++i)
	{
		MySPI_SwapByte(_pDataArray[i]);
	}
	
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}

void W25Q64_SectorErase(uint32_t _Addr)
{
	W25Q64_WriteEnable();
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	MySPI_SwapByte(_Addr >> 16);
	MySPI_SwapByte(_Addr >> 8);
	MySPI_SwapByte(_Addr);
	
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}

void W25Q64_ReadData(uint32_t _Addr, uint8_t* _pDataArray, uint16_t _Count)
{
	uint16_t i = 0;
	
	W25Q64_WriteEnable();
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(_Addr >> 16);
	MySPI_SwapByte(_Addr >> 8);
	MySPI_SwapByte(_Addr);
	
	for(i = 0; i < _Count; ++i)
	{
		_pDataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	
	MySPI_Stop();
}









