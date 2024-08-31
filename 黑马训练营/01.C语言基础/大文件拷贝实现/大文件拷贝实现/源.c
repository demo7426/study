#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>


int CopyFunc(char *tFilePathSrc, char* tFilePathDes, 
	unsigned int tCopyFlag//1 - 拷贝文本文件， 0 - 拷贝二进制文件
)
{
	FILE* mrfp = NULL;
	FILE* mwfp = NULL;
	if (tCopyFlag == 1)
	{
		mrfp = fopen(tFilePathSrc, "r");
		mwfp = fopen(tFilePathDes, "w");
	}
	else if (!tCopyFlag)
	{
		mrfp = fopen(tFilePathSrc, "rb");
		mwfp = fopen(tFilePathDes, "wb");
	}
	
	if (!mrfp || !mwfp)
	{
		perror("file open fail");
		return -1;
	}

	char mbuf[256] = { 0 };
	while (1)
	{
		int mRet = fread(mbuf, 1, sizeof(mbuf), mrfp);
		if (!mRet)
			break;

		fwrite(mbuf, 1, sizeof(mbuf), mwfp);
	}

	fclose(mwfp);
	fclose(mrfp);

	return 0;
}

int main(void)
{
	CopyFunc("01-源.txt", "01-源_副本.txt", 1);
	CopyFunc("01-C简述.avi", "01-C简述_副本.avi", 0);

	return EXIT_SUCCESS;
}
