/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.02.22
描  述: 使用汇编替换函数内部调用代码
备  注:	仅支持x86架构的64位操作系统
修改记录:

  1.  日期: 2024.02.22
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <wtypes.h>

#pragma pack(push, 1)
typedef struct _MYCODE
{
	ULONG Code0;
	USHORT Code1;
	PVOID TargetAddr;
	USHORT Code2;
	ULONG Code3;
	CHAR Code4;
}MYCODE, *PMYCODE;
#pragma pack(pop)

MYCODE g_tNewMyCode = { 0x20EC8348, 0xB848, 0x0, 0xD0FF, 0x20C48348, 0xC3 };
MYCODE g_tOldMyCode = { 0 };

int MyFun(int _X, int _Y)
{
	printf("MyTest is enter.\n");
	return _X - _Y;
}

int MyTest(int _X, int _Y)
{
	printf("MyTest is enter.\n");
	return _X + _Y;
}

int main()
{
	static_assert(sizeof(void*) == 8, "32-bit code generation is not supported.");
    
	DWORD dwOldProtect = 0;			//存储之前的状态
	MEMORY_BASIC_INFORMATION tMemBasicInfo = { 0 };

	VirtualQuery(MyFun, &tMemBasicInfo, sizeof(tMemBasicInfo));														//查询内存区域信息
	VirtualProtect(tMemBasicInfo.BaseAddress, tMemBasicInfo.RegionSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);		//修改内存页属性为可读写的（默认为可读可执行）
	VirtualQuery(MyFun, &tMemBasicInfo, sizeof(tMemBasicInfo));														//查询修改后的内存区域信息

	g_tNewMyCode.TargetAddr = MyTest;

	CopyMemory(&g_tOldMyCode, MyFun, sizeof(MYCODE));																//保存原始的代码段数据
	CopyMemory(MyFun, &g_tNewMyCode, sizeof(MYCODE));																//修改代码段数据

	printf("MyFun(%d, %d) = %d.\n", 5, 4, MyFun(5, 4));
	
	VirtualProtect(tMemBasicInfo.BaseAddress, tMemBasicInfo.RegionSize, dwOldProtect, &dwOldProtect);				//将代码段权限恢复为原状态，防止安全风险

	return EXIT_SUCCESS;
}

