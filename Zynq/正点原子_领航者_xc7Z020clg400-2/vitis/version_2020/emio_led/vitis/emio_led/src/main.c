/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.11
描  述: 	通过库函数实现PS端、PL端按键控制LED灯
备  注:
修改记录:

  1.  日期: 2025.06.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <stdio.h>

#include "xgpiops.h"
#include "xparameters.h"
#include "sleep.h"
#include "xil_types.h"

#define GPIO_DEVICE_ID		XPAR_XGPIOPS_0_DEVICE_ID		//GPIO的设备ID
#define PS_KEY0 			7								//PS_KEY0输出引脚
#define PS_KEY1 			8								//PS_KEY1输出引脚
#define MIO_KEY0 			12								//PS_KEY0输入引脚
#define EMIO_KEY0 			54								//PL_KEY0输入引脚

int main()
{
	printf("GPIO MIO Test!\n");

	XGpioPs_Config* ptXGpioPs_Config = NULL;
	XGpioPs tXGpioPs = { 0 };
	s32 Status = 0;

	//根据器件ID查找器件的配置信息
	ptXGpioPs_Config = XGpioPs_LookupConfig(GPIO_DEVICE_ID);

	//对GPIO的驱动配置进行初始化
	Status = XGpioPs_CfgInitialize(&tXGpioPs, ptXGpioPs_Config, ptXGpioPs_Config->BaseAddr);
	if (Status != XST_SUCCESS)
	{
		return 0;
	}

	//设置引脚方向 0--输入;1--输出;
	XGpioPs_SetDirectionPin(&tXGpioPs, PS_KEY0, 1);
	XGpioPs_SetDirectionPin(&tXGpioPs, PS_KEY1, 1);

	//设置按键为输入，当设置为输入时，不需要再设置输出是否使能
	XGpioPs_SetDirectionPin(&tXGpioPs, MIO_KEY0, 0);
	XGpioPs_SetDirectionPin(&tXGpioPs, EMIO_KEY0, 0);

	//设置输出使能  0--取消使能;1--使能;
	XGpioPs_SetOutputEnablePin(&tXGpioPs, PS_KEY0, 1);
	XGpioPs_SetOutputEnablePin(&tXGpioPs, PS_KEY1, 1);

	while(1)
	{
		//对引脚输出高电平 点亮LED
		XGpioPs_WritePin(&tXGpioPs, PS_KEY0, ~XGpioPs_ReadPin(&tXGpioPs, EMIO_KEY0));
		XGpioPs_WritePin(&tXGpioPs, PS_KEY1, ~XGpioPs_ReadPin(&tXGpioPs, MIO_KEY0));
	}
}

