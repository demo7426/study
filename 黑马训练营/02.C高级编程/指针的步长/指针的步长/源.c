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

//+1之后跳跃的字节数
void test01()
{
	char* p01 = NULL;
	printf("char*\t p + 1 = %d\n", p01 + 1);

	int* p02 = NULL;
	printf("int*\t p + 1 = %d\t\n", p02 + 1);
}

//解引用解出来的字节数
void test02()
{
	int* p = malloc(sizeof(int));
	*p = 1000;

	char* p02 = p;
	printf("%d\n", *((int*)p02));

	free(p);
	p = NULL;
}

//自定义结构体做步长练习
void test03()
{
	Student mStuObj = { "张三", 80, 182 };
	
	printf("Height = %d\n", *(int*)((char*)&mStuObj + offsetof(Student, Height)));//宏函数offsetof计算数据偏移量
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
