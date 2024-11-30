/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	LCD1602.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.30
描  述: LCD1602显示数据
备  注:  
修改记录: 

  1.  日期: 2024.11.30
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>
#include <INTRINS.H>

#include "LCD1602.h"

#define LCD_RS P2_6			//高电平--指令;低电平--数据
#define LCD_RW P2_5
#define LCD_EN P2_7

#define LCD_D P0

static void LCD_Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

/// @brief 写指令
/// @param _Command--指令
/// @return 无
void LCD_WriteCommand(unsigned char _Command)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_D = _Command;
	LCD_EN = 0;
	LCD_EN = 1;
	LCD_Delay1ms();
	LCD_EN = 0;
	LCD_Delay1ms();
}

/// @brief 向DDRAM写入数据
/// @param _Data--数据
/// @return 无
void LCD_WriteData(unsigned char _Data)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_D = _Data;
	LCD_EN = 0;
	LCD_EN = 1;
	LCD_Delay1ms();
	LCD_EN = 0;
	LCD_Delay1ms();
}

/// @brief 设置光标位置
/// @param _Row--行号;
/// @param _Column--列号;
/// @return 无
static void LCD_SetCursor(unsigned char _Row, unsigned char _Column)
{
	if(_Row == 1)
	{
		LCD_WriteCommand(0x80 | (_Column - 1));
	}
	else if(_Row == 2)
	{
		LCD_WriteCommand(0x80 | (_Column - 1 + 0x40));
	}
}

void LCD_Init()
{
	LCD_WriteCommand(0x38);		//八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0C);		//显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);		//数据读写操作后，光标自动加一，画面不动
	LCD_WriteCommand(0x01);		//清屏

}

void LCD_ShowChar(unsigned char _Row, unsigned char _Column, unsigned char _Data)
{
	LCD_SetCursor(_Row, _Column);
	LCD_WriteData(_Data);
}

void LCD_ShowString(unsigned char _Row, unsigned char _Column, unsigned char* _StrData)
{
	int i = 0;
	
	LCD_SetCursor(_Row, _Column);
	
	for(i = 0; _StrData[i] != '\0'; i++)
	{
		LCD_WriteData(_StrData[i]);
	}
}

static unsigned int LCD_Pow(int _Num01, int _Num02)
{
	int i = 0; 
	unsigned int unRes = 1;
	
	for(i = 0; i < _Num02; ++i)
	{
		unRes *= _Num01;
	}
	
	return unRes;
}	

void LCD_ShowNum(unsigned char _Row, unsigned char _Column, unsigned int _Num, unsigned char _NumLen)
{
	int i = 0;
	
	LCD_SetCursor(_Row, _Column);
	
	for(i = _NumLen; i > 0; i--)
	{
		LCD_WriteData(_Num / LCD_Pow(10, i - 1) % 10 + '0');
	}
}

void LCD_ShowSignedNum(unsigned char _Row, unsigned char _Column, int _Num, unsigned char _NumLen)
{
	int i = 0;
	
	LCD_SetCursor(_Row, _Column);
	
	if(_Num < 0)
	{
		LCD_WriteData('-');
		_Num = -_Num;
	}
	else if(_Num >= 0)
	{
		LCD_WriteData('+');
	}
	
	for(i = _NumLen; i > 0; i--)
	{
		LCD_WriteData(_Num / LCD_Pow(10, i - 1) % 10 + '0');
	}
}

void LCD_ShowHexNum(unsigned char _Row, unsigned char _Column, unsigned int _Num, unsigned char _NumLen)
{
	int i = 0;
	
	LCD_SetCursor(_Row, _Column);
	
	for(i = _NumLen; i > 0; i--)
	{
		LCD_WriteData(_Num / LCD_Pow(16, i - 1) % 16 + '0');
	}
}


void LCD_ShowBinNum(unsigned char _Row, unsigned char _Column, unsigned int _Num, unsigned char _NumLen)
{
	int i = 0;
	
	LCD_SetCursor(_Row, _Column);
	
	for(i = _NumLen; i > 0; i--)
	{
		LCD_WriteData(_Num / LCD_Pow(2, i - 1) % 2 + '0');
	}
}

