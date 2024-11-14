/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MatrixLED.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.14
描  述: LED点阵屏模块
备  注:  
修改记录: 

  1.  日期: 2024.11.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "MatrixLED.h"
#include "Delay.h"

sbit RCK = P3^5;					//控制是否将 74HC595 的数据进行输出
sbit SRCLK = P3^6;				//控制把 SER 内部的数据压入 74HC595 中
sbit SER = P3^4;					//暂存数据

/// @brief 阵列显示屏初始化
/// @param 无
/// @return 无
void MatrixLEDInit(void)
{
	SRCLK = 0;
	RCK = 0;
}

/// @brief 设置阵列显示屏
/// @param _Data--显示值;范围为0~7;
/// @return 无
void SetMatrixLED_Byte(unsigned int _Data)
{
	int i=0;
	for(i=0; i < 8; ++i)
	{
		SER = _Data & (0x80 >> i);
		SRCLK = 1;
		SRCLK = 0;
	}
	
	RCK = 1;
	RCK = 0;	
}

/// @brief 设置显示列
/// @param 列索引;范围为0~7;
/// @return 无
void SetColumn(unsigned int _ColumnIndex)
{
	P0 = 0xFF;
	P0 &= ~(0x80 >>  _ColumnIndex);
		
	Delay(1);
	P0 = 0xFF;
}
