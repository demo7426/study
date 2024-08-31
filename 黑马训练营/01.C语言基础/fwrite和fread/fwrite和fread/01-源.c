#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

typedef struct _student
{
	unsigned short Age;//年龄
	char Name[20];//姓氏
	int Score;//分数
}student, * Pstudent;

int WriteStruct(char *tFilePath, student *tStu, 
				unsigned int tElementCount//结构体对象数量
				)
{

	FILE* fp = fopen(tFilePath, "w");
	if (!fp)
	{
		perror("file open fail");
		return -1;
	}

	fwrite(tStu, sizeof(student), 4, fp);

	fclose(fp);
	return 0;
}

int ReadStruct(char* tFilePath,
	unsigned int tElementCount//结构体对象数量
)
{
	struct _student* mStu = malloc(sizeof(student) * tElementCount);
	if (!mStu)
	{
		perror("malloc fail");
		return -1;
	}

	FILE* fp = fopen(tFilePath, "r");
	if (!fp)
	{
		perror("file open fail");
		return -1;
	}

	fread(mStu, sizeof(student), tElementCount, fp);
	for (size_t i = 0; i < tElementCount; i++)
	{
		printf("年龄:%u, 姓氏:%s, 分数: %d\n", (mStu + i)->Age, (mStu + i)->Name, (mStu + i)->Score);
	}
	
	fclose(fp);
	free(mStu);
	return 0;
}

int main(void)
{
	char* mFilePath = "01-源.txt";
	struct _student mStu[4] = {
		18, "Lily", 80,
		19, "Bob", 75,
		18, "Demo", 90,
		20, "David", 86
	};

	WriteStruct(mFilePath, mStu, sizeof(mStu) / sizeof(mStu[0]));
	ReadStruct(mFilePath, sizeof(mStu) / sizeof(mStu[0]));

	return EXIT_SUCCESS;
}
