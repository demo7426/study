#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

int WriteRandFunc(char *tFilePath, unsigned int tRandNumber)
{
	srand(time(NULL));//随机数种子

	FILE* fp = fopen(tFilePath, "w");
	if (!fp)
	{
		perror("File open fail");
		return -1;
	}

	for (size_t i = 0; i < tRandNumber; i++)
	{
		fprintf(fp, "%d\n", rand() % 100);
	}

	fclose(fp);
	return 0;
}

int BubbleSortFunc(char* tFilePath, unsigned int tRandNumber)
{
	int* mArr = malloc(sizeof(int) * tRandNumber);
	if (!mArr)
	{
		perror("malloc fail");
		return -1;
	}
	int mi = 0;

	FILE* fp = fopen(tFilePath, "r");
	if (!fp)
	{
		perror("File open fail");
		return -1;
	}

	while (1)
	{
		fscanf(fp, "%d\n", mArr + mi);
		mi++;
		if (feof(fp))
			break;
	}

	int mtemp = 0;
	for (size_t i = 0; i < tRandNumber; i++)
	{
		for (size_t j = 0; j < tRandNumber - 1 - i; j++)
		{
			if (mArr[j] > mArr[j + 1])
			{
				mtemp = mArr[j];
				mArr[j] = mArr[j + 1];
				mArr[j + 1] = mtemp;
			}
		}
	}

	for (size_t i = 0; i < tRandNumber; i++)
	{
		printf("%d\n", mArr[i]);
	}

	fclose(fp);
	fp = fopen(tFilePath, "w");
	if (!fp)
	{
		perror("File open fail");
		return -1;
	}

	for (size_t i = 0; i < tRandNumber; i++)
	{
		fprintf(fp, "%d\n", mArr[i]);
	}

	fclose(fp);
	free(mArr);
	return 0;
}

int main(void)
{
	char* mFilePath = "01-源.txt";
	int mRandNumber = 10;

	WriteRandFunc(mFilePath, mRandNumber);
	BubbleSortFunc(mFilePath, mRandNumber);

	return EXIT_SUCCESS;
}
