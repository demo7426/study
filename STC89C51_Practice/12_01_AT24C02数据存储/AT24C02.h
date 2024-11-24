/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	AT24C02.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.24
描  述: 对AT24C02内部读写数据模块
备  注:  
修改记录: 

  1.  日期: 2024.11.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __AT24C02_H__
#define __AT24C02_H__

/// @brief 向指定的E²PROM地址写入数据
/// @param _Addr--地址;0~255
/// @param _Data--数据
/// @return 无
void AT24C02_WriteByte(unsigned char _Addr, unsigned char _Data);

/// @brief 从指定的E²PROM地址读取数据
/// @param _Addr--地址;0~255
/// @return 读取到的数据
unsigned char AT24C02_ReadByte(unsigned char _Addr);

#endif