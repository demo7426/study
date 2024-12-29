/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MySPI.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.29
描  述: 软件模拟SPI总线
备  注:  
修改记录: 

  1.  日期: 2024.12.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __MYSPI_H__
#define __MYSPI_H__

/// @brief 初始化
/// @param 无
/// @return 无
void MySPI_Init(void);

/// @brief 开始
/// @param 无
/// @return 无
void MySPI_Start(void);

/// @brief 停止
/// @param 无
/// @return 无
void MySPI_Stop(void);

/// @brief 交换数据
/// @param _Byte--写入给从机的值
/// @return 从机返回的值
uint8_t MySPI_SwapByte(uint8_t _Byte);

#endif
