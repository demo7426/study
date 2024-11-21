/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.22
描  述: 实现蜂鸣器播放提示音
备  注:  
修改记录: 

  1.  日期: 2024.11.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "Key.h"
#include "NixieTube.h"
#include "Buzzer.h"

int main(void)
{
	int nCurKey = 0;
	
	SetNixieTube(1, 0);
	
	while(1)
	{
		nCurKey = GetCurKey();
		if(nCurKey == 0)
		{
			continue;
		}
	
		SetNixieTube(1, nCurKey);
		
		Buzzer_Time(500);
	}
	
	return 0;
}
