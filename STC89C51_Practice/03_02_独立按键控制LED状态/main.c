/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.10
描  述: 独立按键控制LED状态,使用软件消抖
备  注:  
修改记录: 

  1.  日期: 2024.11.10
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/
#include <REGX52.H>

void Delay(unsigned int _Ms)		//@12.000MHz
{
	unsigned char i, j;

	while(_Ms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

int main(void)
{
		while(1)
		{
			if(P3_1 == 0)
			{
				Delay(20);
				while(P3_1==0);
				Delay(20);
				P2_0 = ~P2_0;
			}
		}
}
