/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.12
描  述: 新增PNP处理
备  注:
修改记录:

  1.  日期: 2025.01.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/

#include <ntddk.h>
#include <wdf.h>

#include "Driver.h"
#include "Device.h"

/// <summary>
/// 打印inf文件向注册表添加的参数
/// </summary>
/// <param name="_Driver">驱动对象</param>
/// <returns></returns>
static NTSTATUS PrintRegeditParameter(IN WDFDRIVER _Driver);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDF_DRIVER_CONFIG tWDFDriverConfig = { 0 };
    WDF_OBJECT_ATTRIBUTES tWDFObjAttr = { 0 };
    WDFDRIVER tWDFDriver = { 0 };

    WDF_DRIVER_CONFIG_INIT(&tWDFDriverConfig, EVT_WDF_Driver_Device_Add);

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&tWDFObjAttr, DRIVER_CONTEXT);  //增加上下文对象的创建属性

    //创建框架驱动程序对象
    lNTStatus = WdfDriverCreate(DriverObject, RegistryPath, &tWDFObjAttr, &tWDFDriverConfig, &tWDFDriver);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("创建框架驱动程序对象失败\n"));
        return lNTStatus;
    }

    PrintRegeditParameter(tWDFDriver);

    KdPrint(("驱动加载成功\n"));

    return lNTStatus;
}

static NTSTATUS PrintRegeditParameter(IN WDFDRIVER _Driver)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PDRIVER_CONTEXT ptDriverContext = GetDriverContext(_Driver);
    WDFKEY tWDFKey = { 0 };
    UNICODE_STRING tUnicKeyName;

    //打开驱动程序的 Parameters 注册表项，并检索表示该键的框架注册表项对象的句柄。
    lNTStatus = WdfDriverOpenParametersRegistryKey(_Driver, KEY_READ | KEY_WRITE, WDF_NO_OBJECT_ATTRIBUTES, &tWDFKey);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("WdfDriverOpenParametersRegistryKey is err.\n"));
        return lNTStatus;
    }

    RtlInitUnicodeString(&tUnicKeyName, L"数字");
    lNTStatus = WdfRegistryQueryULong(tWDFKey, &tUnicKeyName, &ptDriverContext->Num);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("WdfRegistryQueryULong is err.\n"));
        return lNTStatus;
    }

    RtlInitUnicodeString(&tUnicKeyName, L"布尔");
    lNTStatus = WdfRegistryQueryULong(tWDFKey, &tUnicKeyName, &ptDriverContext->Boole);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("WdfRegistryQueryULong is err.\n"));
        return lNTStatus;
    }

    UNICODE_STRING tUnicValue;
    USHORT ushValueLen = 0;

    tUnicValue.Buffer = ptDriverContext->StrContent;
    tUnicValue.Length = 0;
    tUnicValue.MaximumLength = sizeof ptDriverContext->StrContent;

    RtlInitUnicodeString(&tUnicKeyName, L"字符串");
    lNTStatus = WdfRegistryQueryUnicodeString(tWDFKey, &tUnicKeyName, &ushValueLen, &tUnicValue);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("WdfRegistryQueryULong is err.\n"));
        return lNTStatus;
    }

    KdPrint(("数字:%d\n", ptDriverContext->Num));
    KdPrint(("布尔:%d\n", ptDriverContext->Boole));
    KdPrint(("字符串:%wZ\n", &tUnicValue));

    return lNTStatus;
}

