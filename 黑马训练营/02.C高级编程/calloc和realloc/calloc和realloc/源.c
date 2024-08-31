#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

/*realloc ���·����ڴ�
	1.������·�����ڴ��ԭ������ô�����ʼ���¿ռ�Ϊ0
	2.�ȿ������ռ䣬����㹻����ôֱ����չ
	3.����������пռ䲻�㣬��ô�����㹻��Ŀռ䣬��ԭ�����ݿ������¿ռ��£��ͷŵ�ԭ�пռ䣬���¿ռ���׵�ַ����
	4.������·�����ڴ��ԭ��С����ô�ͷź���ռ䣬ֻ��Ȩ�޲�������ռ�*/
int ReallocTestFunc()
{
	int nCount = 10;
	int* pnCallocMem = calloc(nCount, sizeof(int));

	if (!pnCallocMem)
	{
		perror("calloc create memory fail");
		return -1;
	}
		
	for (int i = 0; i < nCount; i++)
	{
		pnCallocMem[i] = i;
	}
	printf("calloc:");
	for (int i = 0; i < nCount; i++)
	{
		printf(" %d", pnCallocMem[i]);
	}
	putchar('\n');

	////////////////////////////////////////////////////////////////////////////
	int *pnTempMem = realloc(pnCallocMem, 2 * nCount * sizeof(int));

	if (!pnTempMem)
	{
		perror("realloc create memory fail");
		return -1;
	}
	else
	{
		pnCallocMem = pnTempMem;
	}

	printf("reallocԭ����������ڴ�:\t");
	for (size_t i = 0; i < 2 * nCount; i++)
	{
		printf(" %d", pnCallocMem[i]);
	}
	putchar('\n');
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	pnTempMem = realloc(pnCallocMem, nCount / 2 * sizeof(int));

	if (!pnTempMem)
	{
		perror("realloc create memory fail");
		return -1;
	}
	else
	{
		pnCallocMem = pnTempMem;
	}

	printf("reallocԭ��1/4��С���ڴ�:\t");
	for (size_t i = 0; i < 2 * nCount; i++)
	{
		printf(" %d", pnCallocMem[i]);
	}
	putchar('\n');
	////////////////////////////////////////////////////////////////////////////

	if (!pnCallocMem)
	{
		free(pnCallocMem);
		pnCallocMem = NULL;
	}

	return 0;
}

int MallocTestFunc()
{
	int nCount = 10;
	int* pnMallocMem = malloc(nCount * sizeof(int));

	if (!pnMallocMem)
	{
		perror("malloc create memory fail");
		return -1;
	}

	printf("malloc:");
	for (size_t i = 0; i < nCount; i++)
	{
		printf(" %d", *pnMallocMem++);
	}
	putchar('\n');

	if (!pnMallocMem)
	{
		free(pnMallocMem);
		pnMallocMem = NULL;
	}

	return 0;
}

int CallocTestFunc()
{
	int nCount = 10;
	int* pnCallocMem = calloc(nCount, sizeof(int));//calloc��malloc�����ǣ�calloc����malloc�����Ͻ�����Ķ������ݳ�ʼ��Ϊ0

	if (!pnCallocMem)
	{
		perror("calloc create memory fail");
		return -1;
	}

	printf("calloc:");
	for (size_t i = 0; i < nCount; i++)
	{
		printf(" %d", *pnCallocMem++);
	}
	putchar('\n');

	if (!pnCallocMem)
	{
		free(pnCallocMem);
		pnCallocMem = NULL;
	}

	return 0;
}

int main(void)
{
	MallocTestFunc();
	putchar('\n');
	CallocTestFunc();
	putchar('\n');
	ReallocTestFunc();

	return EXIT_SUCCESS;
}
