#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

/*realloc 重新分配内存
	1.如果重新分配的内存比原来大，那么不会初始化新空间为0
	2.先看后续空间，如果足够，那么直接扩展
	3.如果后续空闲空间不足，那么申请足够大的空间，将原有数据拷贝到新空间下，释放掉原有空间，将新空间的首地址返回
	4.如果重新分配的内存比原来小，那么释放后序空间，只有权限操作申请空间*/
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

	printf("realloc原来两倍大的内存:\t");
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

	printf("realloc原来1/4大小的内存:\t");
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
	int* pnCallocMem = calloc(nCount, sizeof(int));//calloc与malloc区别是，calloc会在malloc基础上将申请的堆区数据初始化为0

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
