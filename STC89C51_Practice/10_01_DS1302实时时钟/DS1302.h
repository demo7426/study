/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	DS1302.h
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

#ifndef __DS1302_H__
#define __DS1302_H_

typedef struct _DS1302_TIME
{
	char Year;				//年
	char Month;				//月
	char Date;				//日
	char Hour;				//时
	char Minute;			//分				
	char Sec;					//秒
}DS1302_TIME, *PDS1302_TIME;

/// @brief DS1302初始化
/// @param 无
/// @return 无
void DS1302_Init(void);

/// @brief DS1302写入对应的数据
/// @param _Command--命令;
/// @param _Data--数据;
/// @return 无
void WriteByte(unsigned char _Command, _Data);

/// @brief DS1302读取对应的数据
/// @param _Command--命令;
/// @return 读取到的数据
unsigned char ReadByte(unsigned char _Command);

/// @brief 设置当前时间
/// @param 时间信息
/// @return 无
void SetCurTime(DS1302_TIME _DS1302_Time);

/// @brief 获取当前时间
/// @param 时间信息
/// @return 无
void GetCurTime(PDS1302_TIME _pDS1302_Time);


#endif