#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

int main01(void)
{
	FILE* fp = NULL;
	//fp = fopen("E:/C++��ϰ/����ѵ��Ӫ/�ļ��Ĵ򿪺͹ر�/�ļ��Ĵ򿪺͹ر�/G����.txt", "r+");//����·��
	fp = fopen("G����.txt", "r+");//���·��
	if (fp == NULL)
	{
		perror("file open fail");
		system("pause");
		return -1;
	}

	printf("file open success\n");
	if (!fclose(fp))
	{
		printf("file close success\n");
	}
	else
	{
		printf("file close fail\n");
	}
	system("pause");
	return EXIT_SUCCESS;
}
