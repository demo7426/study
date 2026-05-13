/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名: main.c
作    者: 钱锐      版本: V0.1.0     新建日期: 2026.04.01
描    述: 软件从sd卡钟读取bmp图片数据到ps ddr中，控制vdma ip核读取ps ddr中的数据，并显示到的lcd屏幕上
备    注:
修改记录:

  1. 日期: 2026.04.01
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#include <stdlib.h>

#include "sleep.h"
#include "./vdma_api/vdma_api.h"
#include "xparameters.h"
#include "xil_cache.h"
#include "./display_ctrl_hdmi/display_ctrl_hdmi.h"
#include "ff.h"

#define AXI_GPIO_CHANNEL1	1

#define AXI_VDMA_DEVICE_ID 	XPAR_AXI_VDMA_0_DEVICE_ID

//挂载SD卡
static int Mount_SD()
{
	static FATFS tFatFS = { 0 };						//注意FATFS对象不能被销毁，fatfs后台后续会使用这个对象的
	const char* pchPath = "0:";

	FRESULT eRes = FR_OK;

	//立即挂载
	eRes = f_mount(&tFatFS, pchPath, 1);
	if(eRes != FR_OK)
	{
		xil_printf("%s: f_mount is failed.\r\n", __FUNCTION__);
		return -2;
	}

	return 0;
}

//加载bmp文件数据
static int LoadBMPFileData(const char* _pFilePath, u8* _pStartBuf)
{
	char chBMPFileHeader[54] = { 0 };		//bmp文件头
	u32 unBMPWidth = 0;						//bmp文件宽度
	u32 unBMPHeight = 0;					//bmp文件高度
	u32 unBMPSize = 0;						//bmp文件大小

	s32 i = 0;

	FIL tFIL;
	FRESULT eRes = FR_OK;
	int nSucReadLen = 0;		//成功读取的字节数

	eRes = f_open(&tFIL, _pFilePath, FA_READ);
	if(eRes != FR_OK)
	{
		xil_printf("%s: f_open is failed.\r\n", __FUNCTION__);
		return -2;
	}

	f_read(&tFIL, chBMPFileHeader, 54, (UINT*)&nSucReadLen);				//读取bmp文件头数据
	unBMPWidth = *(u32*)(chBMPFileHeader + 0x12);
	unBMPHeight = *(u32*)(chBMPFileHeader + 0x16);
	unBMPSize = *(u32*)(chBMPFileHeader + 0x22);
	xil_printf("filepath = %s, width = %u, height = %u, size = %u\r\n",
			_pFilePath, unBMPWidth, unBMPHeight, unBMPSize);

	//读取图片，写入ddr
	for(i = unBMPHeight - 1; i >= 0; --i)		//因为bmp图像数据的存储顺序是从左到右，从下到上的
	{
		f_read(&tFIL, _pStartBuf + i * unBMPWidth * 3, unBMPWidth * 3, (UINT*)&nSucReadLen);
	}

	//关闭文件
	f_close(&tFIL);

	Xil_DCacheFlush();

	return 0;
}

int main()
{
	XAxiVdma InstancePtr;
	VideoMode tVideoMode = { 0 };

	DisplayCtrl tDisplayCtrl = { 0 };

	xil_printf("\n--- Entering main() --- \r\n");

	u8* puchBuf_00 = (u8*)(XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x1000000);

	tVideoMode = VMODE_1920x1080;		//1920*1080分辨率

	//初始化display controler
	DisplayInitialize(&tDisplayCtrl, XPAR_VTC_0_DEVICE_ID);

	//设置video model
	DisplaySetMode(&tDisplayCtrl, &tVideoMode);
	DisplayStart(&tDisplayCtrl);

	//挂载设备
	Mount_SD();

	LoadBMPFileData("0:cartoon.bmp", puchBuf_00);

	xil_printf("VDMA data transmit is success\n\r");

	//配置和开始vdma数据传输
	run_vdma_frame_buffer(
			&InstancePtr,					//vmda
			AXI_VDMA_DEVICE_ID,				//vdma设备id
			tVideoMode.width,				//lcd屏宽度
			tVideoMode.height,				//lcd屏高度
			(int)puchBuf_00,				//ddr起始地址
			0,
			0,								//不使能中断
			ONLY_READ						//vdma读写通道选择，只使能读通道
			);

	while(1)
	{
		sleep(1);
	}

	return 0;
}
