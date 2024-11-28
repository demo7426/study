/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Delay.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.11
描  述: 延时模块
备  注:  
修改记录: 

  1.  日期: 2024.11.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/
#include <REGX52.H>
#include <INTRINS.H>

#include "Delay.h"

void Delay(unsigned int _Ms)		//@11.0592MHz
{
	unsigned char i, j;

	while(_Ms--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}