#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

void WildPointerFunc()//Ұָ�룬һ�������������1��û���ֶ������ڴ��ָ�������2���ֶ�������ڴ��ǲ�����ʹ�õ�
{
	int* mPtr;
	*mPtr = 30;
	printf("%d\n", *mPtr);

	int* mPtr2 = 25;
	*mPtr2 = 30;
	printf("%d\n", *mPtr2);
}

void NullptrFunc()//��ָ��
{
	int* mPtr = NULL;
	*mPtr = 30;
	printf("%d\n", *mPtr);

}

void UniversalptrFunc()//����ָ��
{
	int ma = 10;
	void* mPtr = &ma;
	int* mPtr2 = (int *)mPtr;
	printf("%d\n", *mPtr2);
}

int main(void)
{
	WildPointerFunc();
	NullptrFunc();
	UniversalptrFunc();

	system("pause");
	return EXIT_SUCCESS;
}
