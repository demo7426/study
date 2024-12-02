/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	XPT2046.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.02
描  述: XPT2046数据模块
备  注:  
修改记录: 

  1.  日期: 2024.12.02
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __XPT2046_H__
#define __XPT2046_H__

#define XPT2046_XP_8 			0x9C
#define XPT2046_YP_8 			0xDC
#define XPT2046_VBAT_8 		0xAC
#define XPT2046_AUX_8 		0xEC

#define XPT2046_XP_12 		0x94
#define XPT2046_YP_12 		0xD4
#define XPT2046_VBAT_12 	0xA4
#define XPT2046_AUX_12 		0xE4

/// @brief 获取当前的AD值
/// @param 
/// @return 
unsigned int XPT2046_ReadCurAD(unsigned char _Command);

#endif
