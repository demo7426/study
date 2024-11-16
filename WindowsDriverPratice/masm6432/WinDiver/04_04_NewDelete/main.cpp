/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.16
��  ��: ������������new��delete������
��  ע: ȫ�ֽ�֧������new[]��delete[]������
		�ֲ�֧������new��delete��new[]��delete[]������
�޸ļ�¼:

  1.  ����: 2024.11.16
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

void* __cdecl operator new[](size_t _Size) {
	KdPrint(("ȫ�� new[] ����������."));
	return ExAllocatePool(PagedPool, _Size);
}

void __cdecl operator delete[](void* _pStartAddr) {
	KdPrint(("ȫ�� delete[] ����������."));
	if(_pStartAddr)
		ExFreePool(_pStartAddr);
}

class CMyClass
{
public:
	CMyClass(){
		KdPrint(("CMyClass ���캯��."));
	}
	~CMyClass(){
		KdPrint(("CMyClass ��������."));
	}

	void* operator new(size_t _Size) {
		KdPrint(("CMyClass new ����������."));
		return ExAllocatePool(PagedPool, _Size);
	}

	void operator delete(void* _pStartAddr) {
		KdPrint(("CMyClass delete ����������."));
		if (_pStartAddr)
			ExFreePool(_pStartAddr);
	}
private:


};

/// <summary>
/// new��delete�Ȳ��������ز���
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
/// �ڴ�临�ơ��ڴ�ȽϵȲ���
/// </summary>
VOID Memory_Test02()
{
	CHAR chBuf[129] = { 0 };
	CHAR chBufTmp[129] = { 0 };

	RtlCopyMemory(chBuf, "����һ�������ص����ڴ渴��", strlen("����һ�������ص����ڴ渴��"));
	KdPrint(("%s\n", chBuf));

	RtlZeroMemory(chBuf, sizeof(chBuf));
	RtlMoveMemory(chBuf, "����һ�����ص����ڴ��ƶ�", strlen("����һ�����ص����ڴ��ƶ�"));
	KdPrint(("%s\n", chBuf));

	RtlZeroMemory(chBuf, sizeof(chBuf));
	RtlFillMemory(chBuf, sizeof(chBuf) / 2, 'A');
	KdPrint(("%s\n", chBuf));

	RtlFillMemory(chBufTmp, sizeof(chBufTmp) / 2, 'A');
	if (RtlEqualMemory(chBuf, chBufTmp, sizeof(chBufTmp) > sizeof(chBuf) ? sizeof(chBuf) : sizeof(chBufTmp)))
	{
		KdPrint(("��Ƭ�ڴ��ڲ�����һ��\n"));
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;

	NewAndDelete_Test01();

	KdPrint(("\n"));
	Memory_Test02();

	KdPrint(("�������سɹ�\n"));
	return STATUS_SUCCESS;
}
