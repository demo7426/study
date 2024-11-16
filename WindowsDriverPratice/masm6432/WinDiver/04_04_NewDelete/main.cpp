/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.16
描  述: 在驱动中重载new、delete操作符
备  注: 全局仅支持重载new[]、delete[]操作符
		局部支持重载new、delete、new[]、delete[]操作符
修改记录:

  1.  日期: 2024.11.16
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

void* __cdecl operator new[](size_t _Size) {
	KdPrint(("全局 new[] 操作符重载."));
	return ExAllocatePool(PagedPool, _Size);
}

void __cdecl operator delete[](void* _pStartAddr) {
	KdPrint(("全局 delete[] 操作符重载."));
	if(_pStartAddr)
		ExFreePool(_pStartAddr);
}

class CMyClass
{
public:
	CMyClass(){
		KdPrint(("CMyClass 构造函数."));
	}
	~CMyClass(){
		KdPrint(("CMyClass 析构函数."));
	}

	void* operator new(size_t _Size) {
		KdPrint(("CMyClass new 操作符重载."));
		return ExAllocatePool(PagedPool, _Size);
	}

	void operator delete(void* _pStartAddr) {
		KdPrint(("CMyClass delete 操作符重载."));
		if (_pStartAddr)
			ExFreePool(_pStartAddr);
	}
private:


};

/// <summary>
/// new、delete等操作符重载测试
/// </summary>
VOID NewAndDelete_Test01()
{
	CMyClass* pcMyClass = new CMyClass();
	delete pcMyClass;
	pcMyClass = nullptr;

	PCHAR pchBuf = new CHAR[100];
	delete[] pchBuf;
	pchBuf = nullptr;
}

/// <summary>
/// 内存间复制、内存比较等测试
/// </summary>
VOID Memory_Test02()
{
	CHAR chBuf[129] = { 0 };
	CHAR chBufTmp[129] = { 0 };

	RtlCopyMemory(chBuf, "这是一个不可重叠的内存复制", strlen("这是一个不可重叠的内存复制"));
	KdPrint(("%s\n", chBuf));

	RtlZeroMemory(chBuf, sizeof(chBuf));
	RtlMoveMemory(chBuf, "这是一个可重叠的内存移动", strlen("这是一个可重叠的内存移动"));
	KdPrint(("%s\n", chBuf));

	RtlZeroMemory(chBuf, sizeof(chBuf));
	RtlFillMemory(chBuf, sizeof(chBuf) / 2, 'A');
	KdPrint(("%s\n", chBuf));

	RtlFillMemory(chBufTmp, sizeof(chBufTmp) / 2, 'A');
	if (RtlEqualMemory(chBuf, chBufTmp, sizeof(chBufTmp) > sizeof(chBuf) ? sizeof(chBuf) : sizeof(chBufTmp)))
	{
		KdPrint(("两片内存内部数据一致\n"));
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;

	NewAndDelete_Test01();

	KdPrint(("\n"));
	Memory_Test02();

	KdPrint(("驱动加载成功\n"));
	return STATUS_SUCCESS;
}
