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
/// ���涯̬������Ϣ
/// </summary>
typedef struct _DYNAMICARRAY
{
	//INT32(*Insert)(UINT32 Position, void* data);//��������

	void** pAddres;//�������Ķ�ָ̬�������׵�ַ��ͨ��void*����ÿ��Ԫ�أ�
	UINT32 Capacity;//����
	UINT32 Size;//��С

}DYNAMICARRAY, * PDYNAMICARRAY;

/// <summary>
/// ��ʼ����̬����
/// </summary>
/// <param name="Capacity">��̬��������</param>
/// <returns></returns>
PDYNAMICARRAY DynamicArry_Init(UINT32 Capacity);

/// <summary>
/// ��̬�����������
/// </summary>
/// <param name="Position">��������λ��</param>
/// <param name="data">���ݵ�ַ</param>
/// <returns></returns>
INT32 DynamicArry_Insert(PDYNAMICARRAY tpDynamicArray, UINT32 Position, void* data);

#endif // ! 