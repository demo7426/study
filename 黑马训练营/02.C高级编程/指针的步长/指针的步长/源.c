#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include<stddef.h>

typedef struct _Student
{
	char Name[20];
	int Score;
	int Height;
}Student, *PStudent;

//+1֮����Ծ���ֽ���
void test01()
{
	char* p01 = NULL;
	printf("char*\t p + 1 = %d\n", p01 + 1);

	int* p02 = NULL;
	printf("int*\t p + 1 = %d\t\n", p02 + 1);
}

//�����ý�������ֽ���
void test02()
{
	int* p = malloc(sizeof(int));
	*p = 1000;

	char* p02 = p;
	printf("%d\n", *((int*)p02));

	free(p);
	p = NULL;
}

//�Զ���ṹ����������ϰ
void test03()
{
	Student mStuObj = { "����", 80, 182 };
	
	printf("Height = %d\n", *(int*)((char*)&mStuObj + offsetof(Student, Height)));//�꺯��offsetof��������ƫ����
}

int main(void)
{
	test01();

	printf("\n");
	test02();

	printf("\n");
	test03();

	system("pause");
	return EXIT_SUCCESS;
}
