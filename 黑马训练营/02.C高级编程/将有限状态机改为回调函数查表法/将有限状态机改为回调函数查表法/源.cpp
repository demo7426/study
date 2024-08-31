#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

static void MCS_Printf_1()
{
	printf("MCS_Printf_1\n");
}

static void MCS_Printf_2()
{
	printf("MCS_Printf_2\n");
}

static void MCS_Printf_3()
{
	printf("MCS_Printf_3\n");
}

typedef struct _MCS_Printf
{
	int type;//ִ������
	void (*Printf)();//����ָ��
}MCS_Printf, *PMCS_Printf;

/// <summary>
///  ��ʼ����
/// </summary>
/// <param name="ptr">MCS_Printfָ��</param>
/// <returns></returns>
static int MCS_Init(MCS_Printf* ptr)
{
	int nSize = 0;//�����С
	MCS_Printf tMCS_Printf[] = { {1, MCS_Printf_1}, {2, MCS_Printf_2}, {3, MCS_Printf_3} };

	nSize = sizeof(tMCS_Printf) / sizeof(tMCS_Printf[0]);

	for (size_t i = 0; i < nSize; i++)
		*(ptr + i * sizeof(MCS_Printf)) = tMCS_Printf[i];
	
	return nSize;
}

/// <summary>
/// ����
/// </summary>
/// <param name="Type">ִ������</param>
/// <param name="Capacity">���������</param>
/// <param name="ptr">MCS_Printfָ��</param>
static void MCS_Run(const int Type, int Capacity, const MCS_Printf* ptr)
{
	for (size_t i = 0; i < Capacity; i++)
	{
		if ((ptr + i * sizeof(MCS_Printf))->type == Type)
			(ptr + i * sizeof(MCS_Printf))->Printf();
	}
}

int main(void)
{
	MCS_Printf tMCS_Printf[3];
	int nCapacity = 0;

	nCapacity = MCS_Init(tMCS_Printf);

	MCS_Run(1, nCapacity, tMCS_Printf);
	system("pause");
	return EXIT_SUCCESS;
}
