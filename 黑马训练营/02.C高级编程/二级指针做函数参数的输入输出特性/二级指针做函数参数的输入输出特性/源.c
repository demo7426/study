#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

#define Count 5//��С

//����ָ������ڶ���
int test01()
{
	int** ppnAxis = calloc(Count, sizeof(int*));
	if (!ppnAxis)
	{
		perror("calloc memory fail\n");
		return -1;
	}

	int nArray[Count] = { 0 };

	for (int i = 0; i < Count; i++)
	{
		nArray[i] = i;
		ppnAxis[i] = nArray + i;
	}

	for (int i = 0; i < Count; i++)
	{
		printf("������%d\n", *(ppnAxis[i]));
	}

	free(ppnAxis);
	ppnAxis = NULL;

	return 0;
}

//����ָ�������ջ��
int test02()
{
	int* ppnAxis[Count];

	for (int i = 0; i < Count; i++)
	{
		ppnAxis[i] = malloc(sizeof(int));
		if (!ppnAxis[i])
		{
			perror("malloc memory fail\n");
			return -1;
		}

		*(ppnAxis[i]) = i;
	}
		
	for (int i = 0; i < Count; i++)
	{
		printf("ջ����%d\n", *(ppnAxis[i]));
	}

	for (int i = 0; i < Count; i++)
	{
		free(ppnAxis[i]);
		ppnAxis[i] = NULL;
	}

	return 0;
}

int main(void)
{
	test01();
	putchar('\n');
	test02();

	return EXIT_SUCCESS;
}
