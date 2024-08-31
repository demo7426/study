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
	//fp = fopen("E:/C++练习/黑马训练营/文件的打开和关闭/文件的打开和关闭/fgetc.txt", "w+");//绝对路径
	fp = fopen("feof.txt", "w+");//相对路径
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
	fp = fopen("feof.txt", "r");//相对路径
	if (fp == NULL)
	{
		perror("file open fail");
		system("pause");
		return -1;
	}
	putchar('\n');
	printf("file open success\n");

	char mchar = fgetc(fp);
	while (!feof(fp))//feof函数必须搭配fgetc函数使用（因为feof函数文件指向光标不会移动，但是fgetc函数文件指向光标会移动）
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
