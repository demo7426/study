#ifndef  _DYNAMICARRAY
#define _DYNAMICARRAY

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <stddef.h>

/// <summary>
/// 保存动态数组信息
/// </summary>
typedef struct _DYNAMICARRAY
{
	//INT32(*Insert)(UINT32 Position, void* data);//插入数据

	void** pAddres;//创建出的动态指针数组首地址（通过void*控制每个元素）
	UINT32 Capacity;//容量
	UINT32 Size;//大小

}DYNAMICARRAY, * PDYNAMICARRAY;

/// <summary>
/// 初始化动态数组
/// </summary>
/// <param name="Capacity">动态数组容量</param>
/// <returns></returns>
PDYNAMICARRAY DynamicArry_Init(UINT32 Capacity);

/// <summary>
/// 动态数组插入数据
/// </summary>
/// <param name="Position">插入数据位置</param>
/// <param name="data">数据地址</param>
/// <returns></returns>
INT32 DynamicArry_Insert(PDYNAMICARRAY tpDynamicArray, UINT32 Position, void* data);

#endif // ! 