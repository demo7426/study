/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.09
描  述: 为驱动添加上下文，读取inf文件中在注册表中添加键值数据
备  注:
修改记录:

  1.  日期: 2025.01.9
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/

#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <ntddk.h>
#include <wdf.h>

typedef struct _DRIVER_CONTEXT
{
    DWORD32 Num;            //数字
    DWORD32 Boole;          //布尔
    WCHAR StrContent[64];    //字符串内容
}DRIVER_CONTEXT, *PDRIVER_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DRIVER_CONTEXT, GetDriverContext)            //通过 GetDriverContext 函数即可获取驱动上下文

#endif // !__DRIVER_H__


