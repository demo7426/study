/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.12
描  述: 实现一个windows 驱动的demo
备  注:
		1、编译驱动的方法
		直接生成即可

		2、加载驱动的方法
		使用管理员权限打开cmd终端，使用
			sc create 驱动自定义名称 binpath= 路径 type= kernel
			net start 驱动自定义名称								//加载驱动
			net stop 驱动自定义名称								//卸载驱动
			sc delete 驱动自定义名称								//删除驱动
修改记录:

  1.  日期: 2024.11.12
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

void Unload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("Good bye Driver\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	KdPrint(("Hello Driver\n"));

	DriverObject->DriverUnload = Unload;

	return STATUS_SUCCESS;
}
