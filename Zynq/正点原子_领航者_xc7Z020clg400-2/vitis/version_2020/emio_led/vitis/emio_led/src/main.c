/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.06.11
��  ��: 	ͨ���⺯��ʵ��PS�ˡ�PL�˰�������LED��
��  ע:
�޸ļ�¼:

  1.  ����: 2025.06.11
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.1.0

*************************************************/

#include <stdio.h>

#include "xgpiops.h"
#include "xparameters.h"
#include "sleep.h"
#include "xil_types.h"

#define GPIO_DEVICE_ID		XPAR_XGPIOPS_0_DEVICE_ID		//GPIO���豸ID
#define PS_KEY0 			7								//PS_KEY0�������
#define PS_KEY1 			8								//PS_KEY1�������
#define MIO_KEY0 			12								//PS_KEY0��������
#define EMIO_KEY0 			54								//PL_KEY0��������

int main()
{
	printf("GPIO MIO Test!\n");

	XGpioPs_Config* ptXGpioPs_Config = NULL;
	XGpioPs tXGpioPs = { 0 };
	s32 Status = 0;

	//��������ID����������������Ϣ
	ptXGpioPs_Config = XGpioPs_LookupConfig(GPIO_DEVICE_ID);

	//��GPIO���������ý��г�ʼ��
	Status = XGpioPs_CfgInitialize(&tXGpioPs, ptXGpioPs_Config, ptXGpioPs_Config->BaseAddr);
	if (Status != XST_SUCCESS)
	{
		return 0;
	}

	//�������ŷ��� 0--����;1--���;
	XGpioPs_SetDirectionPin(&tXGpioPs, PS_KEY0, 1);
	XGpioPs_SetDirectionPin(&tXGpioPs, PS_KEY1, 1);

	//���ð���Ϊ���룬������Ϊ����ʱ������Ҫ����������Ƿ�ʹ��
	XGpioPs_SetDirectionPin(&tXGpioPs, MIO_KEY0, 0);
	XGpioPs_SetDirectionPin(&tXGpioPs, EMIO_KEY0, 0);

	//�������ʹ��  0--ȡ��ʹ��;1--ʹ��;
	XGpioPs_SetOutputEnablePin(&tXGpioPs, PS_KEY0, 1);
	XGpioPs_SetOutputEnablePin(&tXGpioPs, PS_KEY1, 1);

	while(1)
	{
		//����������ߵ�ƽ ����LED
		XGpioPs_WritePin(&tXGpioPs, PS_KEY0, ~XGpioPs_ReadPin(&tXGpioPs, EMIO_KEY0));
		XGpioPs_WritePin(&tXGpioPs, PS_KEY1, ~XGpioPs_ReadPin(&tXGpioPs, MIO_KEY0));
	}
}

