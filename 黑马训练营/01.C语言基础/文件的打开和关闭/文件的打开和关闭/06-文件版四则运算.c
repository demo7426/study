#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

double CaculateFunc(char *tStr)
{
	int ma = 0, mb = 0;
	char mc = 0;
	sscanf(tStr, "%d%c%d=\n", &ma, &mc, &mb);
	switch (mc)
	{
	case '*':
		sprintf(tStr, "%d%c%d=%d\n", ma, mc, mb, ma * mb);
		return 0;
	case '/':
		sprintf(tStr, "%d%c%d=%d\n", ma, mc, mb, ma / mb);
		return 0;
	case '+':
		sprintf(tStr, "%d%c%d=%d\n", ma, mc, mb, ma + mb);
		return 0;
	case '-':
		sprintf(tStr, "%d%c%d=%d\n", ma, mc, mb, ma - mb);
		return 0;
	default:
		break;
	}

	return -1;//函数调用失败
}

int main(void)
{
	FILE* fp = fopen("06-文件版四则运算.txt", "r");
	if (fp == NULL)
	{
		perror("fopen fail\n");
		return -1;
	}

	char mbuf[50][100] = { 0 };
	int mLineNumber = 0;//行数

	while (fgets(mbuf[mLineNumber], 100, fp))
	{
		mLineNumber++;
	}
	for (size_t i = 0; i < mLineNumber; i++)
	{
		CaculateFunc(&mbuf[i]);
	}
	
	fclose(fp);

	fp = fopen("06-文件版四则运算.txt", "w+");
	if (fp == NULL)
	{
		perror("fopen fail\n");
		return -1;
	}

	for (size_t i = 0; i < mLineNumber; i++)
	{
		fputs(mbuf[i], fp);
	}
	
	fclose(fp);
	//system("pause");
	return EXIT_SUCCESS;
}
