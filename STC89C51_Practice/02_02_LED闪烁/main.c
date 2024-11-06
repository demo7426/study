/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.07
描  述: 点亮一个LED灯
备  注:  
修改记录: 

  1.  日期: 2024.11.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>
#include <INTRINS.H>

static void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


int main()
{
	while(1)
	{
		P2 = 0xfe;
		Delay500ms();

		P2 = 0xff;
		Delay500ms();
	}
	
	return 0;
}
