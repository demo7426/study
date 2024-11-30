/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	LCD1602.h
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

#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD_Init();
void LCD_ShowChar(unsigned char _Row, unsigned char _Column, unsigned char _Data);
void LCD_ShowString(unsigned char _Row, unsigned char _Column, unsigned char* _StrData);
void LCD_ShowNum(unsigned char _Row, unsigned char _Column, unsigned int _Num, unsigned char _NumLen);
void LCD_ShowSignedNum(unsigned char _Row, unsigned char _Column, int _Num, unsigned char _NumLen);
void LCD_ShowHexNum(unsigned char _Row, unsigned char _Column, unsigned int _Num, unsigned char _NumLen);
void LCD_ShowBinNum(unsigned char _Row, unsigned char _Column, unsigned int _Num, unsigned char _NumLen);

void LCD_WriteData(unsigned char _Data);
void LCD_WriteCommand(unsigned char _Command);

#endif