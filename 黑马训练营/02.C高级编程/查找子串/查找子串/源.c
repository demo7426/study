#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

int MyStrstr(char* pchStr, char* pchSubStr)
{
	int nRtnNum = 0;
	int nRtnMemcmpValue = 0;

	while (*pchStr != "\0")
	{
		if (*pchStr != *pchSubStr)
		{
			pchStr++;
			nRtnNum++;
			continue;
		}

		nRtnMemcmpValue = memcmp(pchStr, pchSubStr, strlen(pchSubStr));
		if (nRtnMemcmpValue == 0)
		{
			return nRtnNum;
		}
		else
		{
			pchStr++;
			nRtnNum++;
		}
	}

	return -1;
}

void test01()
{
	char* pchStr = "abcdefgdnfskjdha";
	char* pchSubStr = "dnf";
	
	int nRtnValue = MyStrstr(pchStr, pchSubStr);

	if (nRtnValue == -1)
	{
		printf("未找到对应字串\n");
	}
	else
	{
		printf("找到对应字串,位置为：%d\n", nRtnValue);
	}
}

int main(void)
{
	test01();

	return EXIT_SUCCESS;
}
