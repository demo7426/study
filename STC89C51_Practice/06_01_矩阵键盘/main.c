/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.11
描  述: 捕获矩阵按下工作，并且显示
备  注:  
修改记录: 

  1.  日期: 2024.11.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "LCD1602.h"

int main(void)
{
	int nCurKey = 0;
	
	LCD_Init();
	
	while(1)
	{
		nCurKey = GetCurMatrixKeyInput();
		if(nCurKey == 0)
			continue;
		
		LCD_ShowNum(1, 1, nCurKey, 2);
	}
	
	return 0;
}
