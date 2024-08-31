#include<stdio.h>
#include"MyMax.h"
#include"MySub.h"

int main()
{
	int nValue[2] = {10, 20};
	printf("%d、%d的最大数为%d\n", nValue[0], nValue[1], MyMaxFunc(nValue[0], nValue[1]));
	printf("%d、%d的差值为%d\n", nValue[0], nValue[1], MySubFunc(nValue[0], nValue[1]));
	printf("Hello world.\n");
	return 0;
}
