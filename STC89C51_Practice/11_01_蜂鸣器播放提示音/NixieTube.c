/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	NixieTube.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.11
描  述: 数码管显示模块
备  注:  
修改记录: 

  1.  日期: 2024.11.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "NixieTube.h"
#include "Delay.h"

//数码管显示子函数
void SetNixieTube(unsigned char _NixieNo, unsigned char _Num)
{
	//数码管段码表
	unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	
	switch(_NixieNo)
	{
		case 1: 	P2_4 = 1; P2_3 = 1; P2_2 = 1; break;
		case 2: 	P2_4 = 1; P2_3 = 1; P2_2 = 0; break;
		case 3: 	P2_4 = 1; P2_3 = 0; P2_2 = 1; break;
		case 4: 	P2_4 = 1; P2_3 = 0; P2_2 = 0; break;
		case 5: 	P2_4 = 0; P2_3 = 1; P2_2 = 1; break;
		case 6: 	P2_4 = 0; P2_3 = 1; P2_2 = 0; break;
		case 7: 	P2_4 = 0; P2_3 = 0; P2_2 = 1; break;
		case 8: 	P2_4 = 0; P2_3 = 0; P2_2 = 0; break;
		default:
			break;
	}
	
	P0 = NixieTable[_Num];
}