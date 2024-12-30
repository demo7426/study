/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	W25Q64.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.29
描  述: 擦除、读写W25Q64 nor flash芯片
备  注:  
修改记录: 

  1.  日期: 2024.12.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __W25Q64_H__
#define __W25Q64_H__

/// @brief 初始化
/// @param 无
/// @return 无
void W25Q64_Init(void);

/// @brief 读取W25Q64的ID
/// @param _pMID--制造商ID
/// @param _pDID--设备ID
/// @return 无
void W25Q64_ReadID(uint8_t* _pMID, uint16_t* _pDID);

/// @brief 写数据
/// @param 无
/// @return 无
void W25Q64_PageProgram(uint32_t _Addr, uint8_t* _pDataArray, uint16_t _Count);

/// @brief 擦除一个扇区的数据
/// @param 无
/// @return 无
void W25Q64_SectorErase(uint32_t _Addr);

/// @brief 读数据
/// @param 无
/// @return 无
void W25Q64_ReadData(uint32_t _Addr, uint8_t* _pDataArray, uint16_t _Count);

#endif
