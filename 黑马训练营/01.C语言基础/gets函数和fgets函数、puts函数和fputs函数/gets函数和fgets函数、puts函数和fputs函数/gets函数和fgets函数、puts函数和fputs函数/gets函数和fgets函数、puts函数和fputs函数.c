#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

int main(void)
{
	char mstr[100];
	gets(mstr);
	puts(mstr);
	printf("%d\n", sizeof(mstr));

	fgets(mstr, sizeof(mstr), stdin);
	fputs(mstr, stdout);

	printf("%d\n", sizeof(mstr));

	system("pause");
	return EXIT_SUCCESS;
}
