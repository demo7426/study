#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>


int CopyFunc(char *tFilePathSrc, char* tFilePathDes, 
	unsigned int tCopyFlag//1 - �����ı��ļ��� 0 - �����������ļ�
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
	CopyFunc("01-Դ.txt", "01-Դ_����.txt", 1);
	CopyFunc("01-C����.avi", "01-C����_����.avi", 0);

	return EXIT_SUCCESS;
}
