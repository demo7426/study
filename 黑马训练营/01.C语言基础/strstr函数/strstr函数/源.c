#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

int StrTimes(const char *tStr, const char *tSubstr)
{
	int mCount = 0;

	char* mPtr = strstr(tStr, tSubstr);

	while (mPtr)
	{
		mCount++;
		mPtr += strlen(tSubstr);
		mPtr = strstr(mPtr, tSubstr);
	}
	return mCount;
}

int main(void)
{
	char mStr[] = "hellolollollo";
	char* mSubstr = "llo";

	printf("%s在%s中出现%d次\n", mSubstr, mStr, StrTimes(mStr, mSubstr));
	system("pause");
	return EXIT_SUCCESS;
}
