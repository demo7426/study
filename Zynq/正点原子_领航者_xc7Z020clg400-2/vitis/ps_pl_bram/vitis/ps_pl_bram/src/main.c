/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.07.04
��  ��: 	ʵ��PS��PL����BRAM�����ݽ���
��  ע:
�޸ļ�¼:

  1.  ����: 2025.07.04
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
#include "pl_bram_rd.h"

#define BRAM_START_ADDR 	0		//bram����ʼ��ַ����Χ��0~1023
#define BRAM_DATA_BYTE 		4		//bram�����ֽڸ�������ΪAXI_Lite������ 32-bit �������ߣ���4�ֽڣ�����

#define PL_BRAM_BASE_ADDR	XPAR_PL_BRAM_RD_0_S00_AXI_BASEADDR			//PL RAM RD����ַ
#define PL_BRAM_START 		PL_BRAM_RD_S00_AXI_SLV_REG0_OFFSET			//PL RAM����ʼ��ַ
#define PL_BRAM_START_ADDR 	PL_BRAM_RD_S00_AXI_SLV_REG1_OFFSET			//PL RAM��ʼ��ַ�Ĵ�����ַ
#define PL_BRAM_LEN 		PL_BRAM_RD_S00_AXI_SLV_REG2_OFFSET			//PL ��RAM���ݵĵ�ַ����

//д�����ݵ�bram
static void WriteDataToBRAM(char* _pData, int _Len);

//��bram��ȡ����
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

//д�����ݵ�bram
static void WriteDataToBRAM(char* _pData, int _Len)
{
	for(int i = BRAM_DATA_BYTE * BRAM_START_ADDR;
			i < BRAM_DATA_BYTE * (BRAM_START_ADDR + _Len);
			i += BRAM_DATA_BYTE)
	{
		XBram_WriteReg(XPAR_BRAM_0_BASEADDR, i, _pData[i / BRAM_DATA_BYTE]);
	}

	//����bram��ȡ���ַ�������
	PL_BRAM_RD_mWriteReg(PL_BRAM_BASE_ADDR, PL_BRAM_LEN, BRAM_DATA_BYTE * _Len);

	//����bram����ʼ��ַ
	PL_BRAM_RD_mWriteReg(PL_BRAM_BASE_ADDR, PL_BRAM_START_ADDR, BRAM_DATA_BYTE * BRAM_START_ADDR);

	//����bram��ʼ�ź�
	PL_BRAM_RD_mWriteReg(PL_BRAM_BASE_ADDR, PL_BRAM_START, 1);

	//����bram��ʼ�ź�
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

