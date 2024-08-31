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

int WriteStruct(char* tFilePath, student* tStu,
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
		printf("年龄:%u, 姓氏:%s,\t 分数: %d\n", (mStu + i)->Age, (mStu + i)->Name, (mStu + i)->Score);
	}

	putchar('\n');
	printf("文件指针从起始地址向后偏移sizeof(student)大小:\n");
	memset(mStu, 0, sizeof(student) * tElementCount);

	fseek(fp, sizeof(student), SEEK_SET);//文件指针从起始地址向后偏移sizeof(student)大小
	fread(mStu, sizeof(student), tElementCount, fp);

	for (size_t i = 0; i < tElementCount; i++)
	{
		printf("年龄:%u, 姓氏:%s,\t 分数: %d\n", (mStu + i)->Age, (mStu + i)->Name, (mStu + i)->Score);
	}

	putchar('\n');
	printf("文件指针从结束地址向前偏移2 * sizeof(student)大小:\n");
	memset(mStu, 0, sizeof(student) * tElementCount);

	fseek(fp, -2 * (int)sizeof(student), SEEK_END);
	fread(mStu, sizeof(student), tElementCount, fp);

	for (size_t i = 0; i < tElementCount; i++)
	{
		printf("年龄:%u, 姓氏:%s,\t 分数: %d\n", (mStu + i)->Age, (mStu + i)->Name, (mStu + i)->Score);
	}

	fseek(fp, 0, SEEK_END);//返回文件指针当前位置与文件起始位置的偏差值
	printf("\n文件大小为：%d\n", ftell(fp));

	rewind(fp);//将文件指针位置重置为文件起始位置
	printf("\n将文件指针位置重置为文件起始位置:\n");
	fread(mStu, sizeof(student), tElementCount, fp);

	for (size_t i = 0; i < tElementCount; i++)
	{
		printf("年龄:%u, 姓氏:%s,\t 分数: %d\n", (mStu + i)->Age, (mStu + i)->Name, (mStu + i)->Score);
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
