/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MatrixLED.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.14
描  述: LED点阵屏模块
备  注:  
修改记录: 

  1.  日期: 2024.11.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __MATRIXLED_H__
#define __MATRIXLED_H__

/// @brief 阵列显示屏初始化
/// @param 无
/// @return 无
void MatrixLEDInit(void);

/// @brief 设置阵列显示屏
/// @param _Data--显示值;范围为0~7;
/// @return 无
void SetMatrixLED_Byte(unsigned int _Data);

/// @brief 设置显示列
/// @param 列索引;范围为0~7;
/// @return 无
void SetColumn(unsigned int _ColumnIndex);


#endif