#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

void WriteFileFunc(char *tStr)
{
	FILE* fp = fopen(tStr, "w");
	if (!fp)
	{
		perror("File open fail");
		return -1;
	}

	fprintf(fp, "%d%c%d = %d\n", 15, '+', 10, 15 + 10);
	fprintf(fp, "%d%c%d = %d\n", 15, '+', 11, 15 + 11);
	fprintf(fp, "%d%c%d = %d\n", 15, '+', 12, 15 + 12);

	fclose(fp);
}

void ReadFileFunc(char* tStr)
{
	int ma, mb, mc;
	char mch;
	FILE* fp = fopen(tStr, "r");
	if (!fp)
	{
		perror("File open fail");
		return -1;
	}

	while (1)
	{
		fscanf(fp, "%d%c%d = %d\n", &ma, &mch, &mb, &mc);
		printf("%d%c%d = %d\n", ma, mch, mb, mc);

		if (feof(fp))
			break;
	}
	fclose(fp);
}

int main(void)
{
	char* mFilepath = "01-Դ.txt";

	WriteFileFunc(mFilepath);
	ReadFileFunc(mFilepath);

	return EXIT_SUCCESS;
}
