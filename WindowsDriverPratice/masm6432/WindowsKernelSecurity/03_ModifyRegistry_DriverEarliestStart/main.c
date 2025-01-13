/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.13
描  述: 通过修改注册表的方式，实现驱动的最早启动
备  注: 测试方法:
        1、必须将.sys文件放置于 C:\Windows\System32\drivers 目录下
        2、在使用 KmdManager。exe加载驱动时，需使用 System32\drivers\03_ModifyRegistry_DriverEarliestStart.sys 名称
        3、HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\03_ModifyRegistry_DriverEarliestStart 下将Start的值修改为 1或2；添加一个新的Group键，值为System Reserved
        4、TODO:Start如果设置为0，无法由引导程序加载进行加载，待研究
修改记录:

  1.  日期: 2025.01.13
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/


#include <ntddk.h>
//#include <wdf.h>

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

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    HANDLE hThread = { 0 };

    DriverObject->DriverUnload = DriverUnload;

    KdPrint(("驱动加载成功\n"));

    PsCreateSystemThread(&hThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, Print_Routine, NULL);

    return lNTStatus;
}

