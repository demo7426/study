/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.04
描  述: 	实现PS、PL基于BRAM的数据交互
备  注:
修改记录:

  1.  日期: 2025.07.04
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <stdio.h>

#include "xparameters.h"
#include "xil_io.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xbram.h"
#include "pl_bram_rd.h"

#define BRAM_START_ADDR 	0		//bram的起始地址，范围：0~1023
#define BRAM_DATA_BYTE 		4		//bram数据字节个数，因为AXI_Lite总线是 32-bit 数据总线（即4字节）对齐

#define PL_BRAM_BASE_ADDR	XPAR_PL_BRAM_RD_0_S00_AXI_BASEADDR			//PL RAM RD及地址
#define PL_BRAM_START 		PL_BRAM_RD_S00_AXI_SLV_REG0_OFFSET			//PL RAM读开始地址
#define PL_BRAM_START_ADDR 	PL_BRAM_RD_S00_AXI_SLV_REG1_OFFSET			//PL RAM起始地址寄存器地址
#define PL_BRAM_LEN 		PL_BRAM_RD_S00_AXI_SLV_REG2_OFFSET			//PL 读RAM数据的地址长度

//写入数据到bram
static void WriteDataToBRAM(char* _pData, int _Len);

//从bram读取数据
static void ReadDataToBRAM(char* _pData, int _Len);

int main()
{
	int i = 0;
	char chWriteBuf[1025] = { 0 };
	char chReadBuf[1025] = { 0 };

	while(1)
	{
		xil_printf("Please enter the parameters and write them into bram\r\n");

		memset(chWriteBuf, 0, sizeof chWriteBuf);
		scanf("%1024s", chWriteBuf);

		WriteDataToBRAM(chWriteBuf, strlen(chWriteBuf));

		ReadDataToBRAM(chReadBuf, strlen(chWriteBuf));

		for(i = 0; i < strlen(chWriteBuf); i++)
		{
			xil_printf("chReadBuf[%d] = %c\r\n", i, chReadBuf[i]);
		}
	}

	return 0;
}

//写入数据到bram
static void WriteDataToBRAM(char* _pData, int _Len)
{
	for(int i = BRAM_DATA_BYTE * BRAM_START_ADDR;
			i < BRAM_DATA_BYTE * (BRAM_START_ADDR + _Len);
			i += BRAM_DATA_BYTE)
	{
		XBram_WriteReg(XPAR_BRAM_0_BASEADDR, i, _pData[i / BRAM_DATA_BYTE]);
	}

	//设置bram读取的字符串长度
	PL_BRAM_RD_mWriteReg(PL_BRAM_BASE_ADDR, PL_BRAM_LEN, BRAM_DATA_BYTE * _Len);

	//设置bram的起始地址
	PL_BRAM_RD_mWriteReg(PL_BRAM_BASE_ADDR, PL_BRAM_START_ADDR, BRAM_DATA_BYTE * BRAM_START_ADDR);

	//拉高bram开始信号
	PL_BRAM_RD_mWriteReg(PL_BRAM_BASE_ADDR, PL_BRAM_START, 1);

	//拉低bram开始信号
	PL_BRAM_RD_mWriteReg(PL_BRAM_BASE_ADDR, PL_BRAM_START, 0);
}

static void ReadDataToBRAM(char* _pData, int _Len)
{
	for(int i = BRAM_DATA_BYTE * BRAM_START_ADDR;
				i < BRAM_DATA_BYTE * (BRAM_START_ADDR + _Len);
				i += BRAM_DATA_BYTE)
	{
		_pData[i / BRAM_DATA_BYTE] = XBram_ReadReg(XPAR_BRAM_0_BASEADDR, i);
	}
}

