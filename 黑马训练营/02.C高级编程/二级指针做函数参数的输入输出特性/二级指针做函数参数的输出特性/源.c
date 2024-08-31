#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

#define Count 5//ด๓ะก

int AllocateSpace(int **p)
{
	int* pTemp = calloc(Count, sizeof(int));
	if (!pTemp)
	{
		perror("calloc memory fail\n");
		return -1;
	}
	*p = pTemp;
	return 0;
}

void ArrayPrintf(const int** p)
{
	for (size_t i = 0; i < Count; i++)
	{
		printf("%d\n", (*p)[i]);
	}
}

void freeSpace(const int** p)
{
	if (*p)
	{
		free(*p);
		*p = NULL;
	}
}

int test01()
{
	int* pAxis = NULL;

	AllocateSpace(&pAxis);
	ArrayPrintf(&pAxis);
	freeSpace(&pAxis);

	return 0;
}

int main(void)
{
	test01();

	return EXIT_SUCCESS;
}
