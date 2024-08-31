#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

void Writefile04()
{
	FILE* fp = NULL;
	//fp = fopen("E:/C++��ϰ/����ѵ��Ӫ/�ļ��Ĵ򿪺͹ر�/�ļ��Ĵ򿪺͹ر�/fgetc.txt", "w+");//����·��
	fp = fopen("feof.txt", "w+");//���·��
	if (fp == NULL)
	{
		perror("file open fail");
		system("pause");
		return -1;
	}

	int ret = fputc('a', fp);
	if (ret == -1)
		perror("fputc fail!");

	ret = fputc('b', fp);
	if (ret == -1)
		perror("fputc fail!");

	ret = fputc(-1, fp);
	if (ret == -1)
		perror("fputc fail!");

	ret = fputc('c', fp);
	if (ret == -1)
		perror("fputc fail!");

	ret = fputc('d', fp);
	if (ret == -1)
		perror("fputc fail!");


	printf("file open success\n");
	printf("Start write\n");
	if (!fclose(fp))
	{
		printf("file close success\n");
	}
	else
	{
		printf("file close fail\n");
	}
}

void Readfile04()
{
	FILE* fp = NULL;
	fp = fopen("feof.txt", "r");//���·��
	if (fp == NULL)
	{
		perror("file open fail");
		system("pause");
		return -1;
	}
	putchar('\n');
	printf("file open success\n");

	char mchar = fgetc(fp);
	while (!feof(fp))//feof�����������fgetc����ʹ�ã���Ϊfeof�����ļ�ָ���겻���ƶ�������fgetc�����ļ�ָ������ƶ���
	{
		printf("%d\n", mchar);
		mchar = fgetc(fp);
	}

	if (!fclose(fp))
	{
		printf("file close success\n");
	}
	else
	{
		printf("file close fail\n");
	}
}

int main04(void)
{
	Writefile04();
	Readfile04();

	system("pause");
	return EXIT_SUCCESS;
}
