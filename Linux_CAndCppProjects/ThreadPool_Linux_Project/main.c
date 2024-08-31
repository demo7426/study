#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include"ThreadPool.h"


void TaskCallFunc(void* _Arg)
{
	printf("Thread %ld is working, num = %ld\n", pthread_self(), *(int*)_Arg);
	usleep(100000);
}

int main()
{
    THREADPOOL_INFO* ptThreadPool_Info = ThreadPool_Create(3, 8, 100);
	int nLength = 500;
	int* pnNum = (int*)malloc(sizeof(int) * nLength);

	for (int i = 0; i < nLength; i++)
	{
		*(pnNum + i) = i;
		ThreadPoolAdd(ptThreadPool_Info, TaskCallFunc, pnNum + i);
	}

	sleep(30);
	free(pnNum);

	ThreadPool_Destroy(ptThreadPool_Info);

    return 0;
}