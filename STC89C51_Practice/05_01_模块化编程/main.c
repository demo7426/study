/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.11
描  述: 使用模块化编程，进行动态数码管显示
备  注:  
修改记录: 

  1.  日期: 2024.11.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "Delay.h"
#include "NixieTube.h"

int main(void)
{
	SetNixieTube(1, 1);
	SetNixieTube(2, 2);
	SetNixieTube(3, 3);
	
	return 0;
}
