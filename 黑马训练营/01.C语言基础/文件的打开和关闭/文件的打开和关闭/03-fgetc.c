#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

void Writefile()
{
	FILE* fp = NULL;
	//fp = fopen("E:/C++��ϰ/����ѵ��Ӫ/�ļ��Ĵ򿪺͹ر�/�ļ��Ĵ򿪺͹ر�/fgetc.txt", "w+");//����·��
	fp = fopen("fgetc.txt", "w+");//���·��
	if (fp == NULL)
	{
		perror("file open fail");
		system("pause");
		return -1;
	}

	char mc = 'a';
	int ret = 0;
	while (mc <= 'z')
	{
		ret = fputc(mc, fp);
		mc++;
		if (ret == -1)
			perror("fputc fail!");
	}

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

void Readfile()
{
	FILE* fp = NULL;
	fp = fopen("fgetc.txt", "r");//���·��
	if (fp == NULL)
	{
		perror("file open fail");
		system("pause");
		return -1;
	}
	putchar('\n');
	printf("file open success\n");

	char mchar = fgetc(fp);
	while (mchar != EOF)
	{
		printf("%c\n", mchar);
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

int main03(void)
{
	Writefile();
	Readfile();

	system("pause");
	return EXIT_SUCCESS;
}
