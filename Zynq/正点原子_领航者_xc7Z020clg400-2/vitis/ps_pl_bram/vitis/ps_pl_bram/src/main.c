/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.06.23
��  ��: 	ͨ���Զ����ip����led�Ƶ�����/��˸Ƶ��
��  ע:
�޸ļ�¼:

  1.  ����: 2025.06.23
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.1.0

*************************************************/

#include <stdio.h>

#include "xparameters.h"
#include "xil_io.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xbram.h"

#define BRAM_START_ADDR 	0		//bram����ʼ��ַ����Χ��0~1023
#define BRAM_DATA_BYTE 		4		//bram�����ֽڸ�������ΪAXI_Lite������ 32-bit �������ߣ���4�ֽڣ�����

//д�����ݵ�bram
static void WriteDataToBRAM(char* _pData, int _Len);

//��bram��ȡ����
static void ReadDataToBRAM(char* _pData, int _Len);

int main()
{
	char chWriteBuf[1025] = { 0 };
	char chReadBuf[1025] = { 0 };

	while(1)
	{
		xil_printf("Please enter the parameters and write them into bram");

		memset(chWriteBuf, 0, sizeof chWriteBuf);
		scanf("%1024s", chWriteBuf);

		WriteDataToBRAM(chWriteBuf, strlen(chWriteBuf));

		ReadDataToBRAM(chReadBuf, strlen(chWriteBuf));
	}

	return 0;
}

//д�����ݵ�bram
static void WriteDataToBRAM(char* _pData, int _Len)
{
	for(int i = BRAM_DATA_BYTE * BRAM_START_ADDR;
			i < BRAM_DATA_BYTE * (BRAM_START_ADDR + _Len);
			i += BRAM_DATA_BYTE)
	{
		XBram_WriteReg(XPAR_BRAM_0_BASEADDR, i, _pData[i / BRAM_DATA_BYTE]);
	}
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

