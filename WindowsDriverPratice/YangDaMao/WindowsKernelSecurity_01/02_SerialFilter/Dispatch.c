/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Dispatch.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.02.19
描  述: 派遣函数
备  注:
修改记录:

  1.  日期: 2024.02.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include "Dispatch.h"
#include "Device.h"

NTSTATUS Dispatch_Default(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICEEXTENSION pDevExt = DeviceObject->DeviceExtension;

	IoSkipCurrentIrpStackLocation(Irp);

	lNTStatus = IoCallDriver(pDevExt->pFDO, Irp);

	return lNTStatus;
}

NTSTATUS Dispatch_Pnp(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	return Dispatch_Default(DeviceObject, Irp);
}

NTSTATUS Dispatch_Power(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICEEXTENSION pDevExt = DeviceObject->DeviceExtension;

	PoStartNextPowerIrp(Irp);									//向电源管理器表明驱动程序已准备好处理下一个电源 IRP
	IoSkipCurrentIrpStackLocation(Irp);

	//从 Windows Vista 开始，驱动程序应调用 IoCallDriver，而不是 PoCallDriver 将电源 IRP 传递给下一个较低级别的驱动程序。 
	//但是，在 Windows Server 2003、Windows XP 和 Windows 2000 上，驱动程序必须调用 PoCallDriver，而不是 IoCallDriver 才能将电源 IRP 传递给下一个较低级别的驱动程序。
	lNTStatus = IoCallDriver(pDevExt->pFDO, Irp);

	return lNTStatus;
}

NTSTATUS Dispatch_Write(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);
	ULONG ulWriteLen = 0;

	__try
	{
		PVOID systemBuffer = Irp->AssociatedIrp.SystemBuffer;
		PVOID pvBuf = NULL;
		PDEVICEEXTENSION pDevExt = DeviceObject->DeviceExtension;

		ulWriteLen = pIOStack->Parameters.Write.Length;

		if (systemBuffer && *(PCHAR)systemBuffer == 'a')			//串口过滤
		{
			KdPrint(("%s\n", (PCHAR)systemBuffer));

			IoSkipCurrentIrpStackLocation(Irp);

			lNTStatus = IoCallDriver(pDevExt->pFDO, Irp);
			return lNTStatus;
		}
		else
		{
			ulWriteLen = 0;
			KdPrint(("SystemBuffer is null\n"));
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("写入数据抛出异常\n"));
		lNTStatus = GetExceptionCode();
	}

	Irp->IoStatus.Status = lNTStatus;
	Irp->IoStatus.Information = ulWriteLen;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}



