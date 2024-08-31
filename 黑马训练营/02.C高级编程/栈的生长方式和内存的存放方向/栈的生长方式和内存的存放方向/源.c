#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

//栈的生长方式
void test01()
{
	int ma = 10;//栈底
	int mb = 10;
	int mc = 10;
	int md = 10;//栈顶

	printf("ma = %d\n", &ma);
	printf("mb = %d\n", &mb);
	printf("mc = %d\n", &mc);
	printf("md = %d\n", &md);
}

//内存的存放方向
void test02()
{
	int ma = 0x11223344;//地址存放顺序由高到低
	char* p = &ma;

	printf("%x\n", *p);//44放在的低地址
	printf("%x\n", *(p + 1));
}

int main(void)
{
	test01();
	test02();
	return EXIT_SUCCESS;
}
