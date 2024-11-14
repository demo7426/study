/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.14
描  述: LED点阵屏显示动画
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

int main(void)
{
	int i = 0;
	int	nOffset = 0;	//偏移量
	unsigned int nShowDatas[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
																0xFF,0x08,0x08,0x08,0xFF,0x00,0x0E,0x15,
																0x15,0x15,0x0C,0x00,0x7E,0x01,0x02,0x00,
																0x7E,0x01,0x02,0x00,0x06,0x09,0x09,0x06,
																0x00,0x7D,0x00,0x00,0x00,0x00,0x00,0x00,
																0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	
	MatrixLEDInit();
	
	while(1)
	{
		for(i=0; i < sizeof(nShowDatas) / sizeof(nShowDatas[0]); ++i)
		{
			SetMatrixLED_Byte(nShowDatas[i + nOffset]);
			SetColumn(i);
			
		}
		
		nOffset++;
		if(nOffset > sizeof(nShowDatas) / sizeof(nShowDatas[0]) - 8)
			nOffset = 0;
	}
	
	return 0;
}
	
