#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

int main05(void)
{
	FILE* fp = fopen("05-fgetsºÍfputs.txt", "w");
	if (fp == NULL)
	{
		perror("fopen fail\n");
		return -1;
	}

	char mbuf[4096] = { 0 };
	while (1)
	{
		fgets(mbuf, 4096, stdin);
		if (strcmp(mbuf, ":end\n") == 0)
			break;
		fputs(mbuf, fp);
	}
	
	fclose(fp);

	system("pause");
	return EXIT_SUCCESS;
}
