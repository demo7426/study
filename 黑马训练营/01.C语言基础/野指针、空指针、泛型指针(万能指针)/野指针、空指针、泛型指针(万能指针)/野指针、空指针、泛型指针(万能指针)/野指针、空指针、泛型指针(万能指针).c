#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

void WildPointerFunc()//野指针，一共有两种情况，1：没有手动分配内存给指针变量，2：手动分配的内存是不可以使用的
{
	int* mPtr;
	*mPtr = 30;
	printf("%d\n", *mPtr);

	int* mPtr2 = 25;
	*mPtr2 = 30;
	printf("%d\n", *mPtr2);
}

void NullptrFunc()//空指针
{
	int* mPtr = NULL;
	*mPtr = 30;
	printf("%d\n", *mPtr);

}

void UniversalptrFunc()//万能指针
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
