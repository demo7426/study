#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

typedef struct _student
{
	unsigned short Age;//����
	char Name[20];//����
	int Score;//����
}student, * Pstudent;

int WriteStruct(char* tFilePath, student* tStu,
	unsigned int tElementCount//�ṹ���������
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
	unsigned int tElementCount//�ṹ���������
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
		printf("����:%u, ����:%s,\t ����: %d\n", (mStu + i)->Age, (mStu + i)->Name, (mStu + i)->Score);
	}

	putchar('\n');
	printf("�ļ�ָ�����ʼ��ַ���ƫ��sizeof(student)��С:\n");
	memset(mStu, 0, sizeof(student) * tElementCount);

	fseek(fp, sizeof(student), SEEK_SET);//�ļ�ָ�����ʼ��ַ���ƫ��sizeof(student)��С
	fread(mStu, sizeof(student), tElementCount, fp);

	for (size_t i = 0; i < tElementCount; i++)
	{
		printf("����:%u, ����:%s,\t ����: %d\n", (mStu + i)->Age, (mStu + i)->Name, (mStu + i)->Score);
	}

	putchar('\n');
	printf("�ļ�ָ��ӽ�����ַ��ǰƫ��2 * sizeof(student)��С:\n");
	memset(mStu, 0, sizeof(student) * tElementCount);

	fseek(fp, -2 * (int)sizeof(student), SEEK_END);
	fread(mStu, sizeof(student), tElementCount, fp);

	for (size_t i = 0; i < tElementCount; i++)
	{
		printf("����:%u, ����:%s,\t ����: %d\n", (mStu + i)->Age, (mStu + i)->Name, (mStu + i)->Score);
	}

	fseek(fp, 0, SEEK_END);//�����ļ�ָ�뵱ǰλ�����ļ���ʼλ�õ�ƫ��ֵ
	printf("\n�ļ���СΪ��%d\n", ftell(fp));

	rewind(fp);//���ļ�ָ��λ������Ϊ�ļ���ʼλ��
	printf("\n���ļ�ָ��λ������Ϊ�ļ���ʼλ��:\n");
	fread(mStu, sizeof(student), tElementCount, fp);

	for (size_t i = 0; i < tElementCount; i++)
	{
		printf("����:%u, ����:%s,\t ����: %d\n", (mStu + i)->Age, (mStu + i)->Name, (mStu + i)->Score);
	}

	fclose(fp);
	free(mStu);
	return 0;
}

int main(void)
{
	char* mFilePath = "01-Դ.txt";
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
