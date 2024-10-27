/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	cc.h
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.08.04
描  述: 类型别名文件
备  注:
修改记录:

  1.  日期: 2024.08.04
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#ifndef _CC_H
#define _CC_H

#define __I                 volatile
#define __O                 volatile
#define __IO                volatile

typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;
typedef signed long long    int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef signed long long    s64;

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

#endif