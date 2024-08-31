#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

int main02(void)
{
	FILE* fp = NULL;
	//fp = fopen("E:/C++练习/黑马训练营/文件的打开和关闭/文件的打开和关闭/G代码.txt", "w+");//绝对路径
	fp = fopen("G代码.txt", "w+");//相对路径
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
