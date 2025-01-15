/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.15
描  述: 驱动的重新初始化
备  注: 
修改记录:

  1.  日期: 2025.01.15
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/


#include <ntddk.h>
#include <wdf.h>

VOID Print_Routine(_In_ PVOID _pContext)
{
    LARGE_INTEGER tTimeout = RtlConvertLongToLargeInteger(-10 * 1000 * 500);            //延迟时间为500ms
    UINT32 unCounter = 0;                                                               //计数

    while (TRUE)
    {
        KdPrint(("Print_Routine is runnig, unCounter = %u\n", unCounter++));

        KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);
    }

}

//驱动的重新初始化函数
VOID Driver_Reinitialize(_In_ struct _DRIVER_OBJECT* DriverObject, _In_opt_ PVOID Context, _In_ ULONG Count)
{
    HANDLE hThread = { 0 };

    PsCreateSystemThread(&hThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, Print_Routine, NULL);
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;

    DriverObject->DriverUnload = DriverUnload;

    KdPrint(("驱动加载成功\n"));

    //IoRegisterBootDriverReinitialization(DriverObject, Driver_Reinitialize, NULL);    //经过测试win7_sp1_x86操作系统不会生效，即不会进行重新初始化操作
    IoRegisterDriverReinitialization(DriverObject, Driver_Reinitialize, NULL);

    return lNTStatus;
}

