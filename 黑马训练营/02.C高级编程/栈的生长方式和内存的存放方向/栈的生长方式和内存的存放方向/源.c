#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

//ջ��������ʽ
void test01()
{
	int ma = 10;//ջ��
	int mb = 10;
	int mc = 10;
	int md = 10;//ջ��

	printf("ma = %d\n", &ma);
	printf("mb = %d\n", &mb);
	printf("mc = %d\n", &mc);
	printf("md = %d\n", &md);
}

//�ڴ�Ĵ�ŷ���
void test02()
{
	int ma = 0x11223344;//��ַ���˳���ɸߵ���
	char* p = &ma;

	printf("%x\n", *p);//44���ڵĵ͵�ַ
	printf("%x\n", *(p + 1));
}

int main(void)
{
	test01();
	test02();
	return EXIT_SUCCESS;
}
