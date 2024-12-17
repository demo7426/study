/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	AD.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.17
描  述: AD模数转换
备  注:  
修改记录: 

  1.  日期: 2024.12.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __AD_H__
#define __AD_H__

/// @brief 初始化
/// @param 无
/// @return 无
void AD_Init(void);

/// @brief 获取模拟量转换后的值
/// @param 无
/// @return 模拟量转换后的值
unsigned short AD_GetValue(void);

#endif
