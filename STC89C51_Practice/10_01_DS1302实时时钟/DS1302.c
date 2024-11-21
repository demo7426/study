/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	DS1302.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.17
描  述: DS1302时钟模块
备  注:  
修改记录: 

  1.  日期: 2024.11.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/
#include <REGX52.H>
#include <stdlib.h>

#include "DS1302.h"

#define DS1302_CE 			P3_5
#define DS1302_SCLK 		P3_6
#define DS1302_IO 			P3_4
	
#define DS1302_WRITE_SEC 	0x80			//秒的写入基地址
#define DS1302_WRITE_MINUTE 0x82			//分的写入基地址	
#define DS1302_WRITE_HOUR 	0x84			//时的写入基地址	
#define DS1302_WRITE_DATE 	0x86			//日的写入基地址	
#define DS1302_WRITE_MONTH 	0x88			//月的写入基地址	
#define DS1302_WRITE_DAY 	0x8A			//星期的写入基地址
#define DS1302_WRITE_YEAR 	0x8C			//年的写入基地址
#define DS1302_WRITE_WP 	0x8E			//写保护基地址	

void DS1302_Init(void)
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
	DS1302_IO = 0;

//	WriteByte(0x8E, 0x00);
//	WriteByte(0x80, 0x00);
}

void WriteByte(unsigned char _Command, _Data)
{
	int i =0;
	
	DS1302_CE = 1;
	
	//写入数据需要特定的时序相对应才能成功写入
	for(i = 0; i < 8; ++i)
	{
		DS1302_IO = _Command & (0x01 << i);
		DS1302_SCLK = 1;
		
		//电平的变化时间不可以太短，具体DS1302芯片参考手册，因为DS1302线片时钟较小，执行代码较慢，故不需要延时		
		DS1302_SCLK = 0;
	}
	
	for(i = 0; i < 8; ++i)
	{
		DS1302_IO = _Data & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	DS1302_CE = 0;
}

unsigned char ReadByte(unsigned char _Command)
{
	int i =0;
	unsigned char uchData = 0;
	
	DS1302_CE = 1;
	
	//读取数据需要特定的时序相对应才能成功写入
	for(i = 0; i < 8; ++i)
	{
		DS1302_IO = _Command & (0x01 << i);
		DS1302_SCLK = 0;
		
		//电平的变化时间不可以太短，具体DS1302芯片参考手册，因为DS1302线片时钟较小，执行代码较慢，故不需要延时		
		DS1302_SCLK = 1;
	}
	
	for(i = 0; i < 8; ++i)
	{
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		
		if(DS1302_IO)
			uchData |= (0x01 << i);
	}
	
	DS1302_CE = 0;
	DS1302_IO = 0;							//读取后将IO设置为0，否则读出的数据会出错
	return uchData;
}

void SetCurTime(DS1302_TIME _DS1302_Time)
{	
	//寄存器内部的值采用BCD编码，故需要转换
	_DS1302_Time.Year = _DS1302_Time.Year / 10 * 16 + _DS1302_Time.Year % 10;
	_DS1302_Time.Month = _DS1302_Time.Month / 10 * 16 + _DS1302_Time.Month % 10;
	_DS1302_Time.Date = _DS1302_Time.Date / 10 * 16 + _DS1302_Time.Date % 10;
	_DS1302_Time.Hour = _DS1302_Time.Hour / 10 * 16 + _DS1302_Time.Hour % 10;
	_DS1302_Time.Minute = _DS1302_Time.Minute / 10 * 16 + _DS1302_Time.Minute % 10;
	_DS1302_Time.Sec = _DS1302_Time.Sec / 10 * 16 + _DS1302_Time.Sec % 10;
	
	WriteByte(DS1302_WRITE_WP, 0x00);
	WriteByte(DS1302_WRITE_YEAR, _DS1302_Time.Year);
	WriteByte(DS1302_WRITE_MONTH, _DS1302_Time.Month);
	WriteByte(DS1302_WRITE_DATE, _DS1302_Time.Date);
	WriteByte(DS1302_WRITE_HOUR, _DS1302_Time.Hour);
	WriteByte(DS1302_WRITE_MINUTE, _DS1302_Time.Minute);
	WriteByte(DS1302_WRITE_SEC, _DS1302_Time.Sec);
	WriteByte(DS1302_WRITE_WP, 0x80);
}

void GetCurTime(PDS1302_TIME _pDS1302_Time)
{
	if(_pDS1302_Time == NULL)
		return;
	
	_pDS1302_Time->Year = ReadByte(DS1302_WRITE_YEAR | 0x01);
	_pDS1302_Time->Month = ReadByte(DS1302_WRITE_MONTH | 0x01);
	_pDS1302_Time->Date = ReadByte(DS1302_WRITE_DATE | 0x01);
	_pDS1302_Time->Hour = ReadByte(DS1302_WRITE_HOUR | 0x01);
	_pDS1302_Time->Minute = ReadByte(DS1302_WRITE_MINUTE | 0x01);
	_pDS1302_Time->Sec = ReadByte(DS1302_WRITE_SEC | 0x01);
	
	//寄存器内部的值采用BCD编码，故需要转换
	_pDS1302_Time->Year = _pDS1302_Time->Year / 16 * 10 + _pDS1302_Time->Year % 16;
	_pDS1302_Time->Month = _pDS1302_Time->Month / 16 * 10 + _pDS1302_Time->Month % 16;
	_pDS1302_Time->Date = _pDS1302_Time->Date / 16 * 10 + _pDS1302_Time->Date % 16;
	_pDS1302_Time->Hour = _pDS1302_Time->Hour / 16 * 10 + _pDS1302_Time->Hour % 16;
	_pDS1302_Time->Minute = _pDS1302_Time->Minute / 16 * 10 + _pDS1302_Time->Minute % 16;
	_pDS1302_Time->Sec = _pDS1302_Time->Sec / 16 * 10 + _pDS1302_Time->Sec % 16;
}
