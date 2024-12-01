/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.01
描  述: LED呼吸灯
备  注:  
修改记录: 

  1.  日期: 2024.12.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/
#include <REGX52.H>

#define LED_01 P2_0

void Delay(unsigned char _Counter)
{
	while(_Counter--);
}

int main(void)
{
	int i = 0;
	int j = 0;
	
	while(1)
	{
		for(i = 0; i <= 100; i++)
		{
			for(j = 0; j <= 20; j++)
			{
				LED_01 = 0;
				Delay(i);
				LED_01 = 1;
				Delay(100 - i);
			}
		}
		
		for(i = 0; i <= 100; i++)
		{
			for(j = 0; j <= 20; j++)
			{
				LED_01 = 1;
				Delay(i);
				LED_01 = 0;
				Delay(100 - i);
			}
		}
	}
	
	return 0;
}

