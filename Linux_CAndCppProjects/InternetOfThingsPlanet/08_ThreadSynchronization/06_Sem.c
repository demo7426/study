//Linux 线程信号量
//一共5个API，分别为sem_init、sem_destroy、sem_wait、sem_trywait、sem_post

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<semaphore.h>
#include <unistd.h>

int g_nNum = 0;
sem_t g_sem;

void *THreadFunc01(void *_Arg)
{
    while (1)
    {
        sem_wait(&g_sem);
        printf("THreadFunc01:%ld\n", g_nNum);
        g_nNum++;
        sem_post(&g_sem);
    }
    

    return NULL;
}

void *THreadFunc02(void *_Arg)
{
    while (1)
    {
        sem_wait(&g_sem);
        printf("THreadFunc02:%ld\n", g_nNum);
        g_nNum++;
        sem_post(&g_sem);
    }
    return NULL;
}

int Test_Mutex(void)
{
    pthread_t unpthread_t[2];

    sem_init(&g_sem, 0, 1);

    pthread_create(unpthread_t, NULL, THreadFunc01, NULL);
    pthread_create(unpthread_t + 1, NULL, THreadFunc02, NULL);

    pthread_join(*unpthread_t, NULL);
    pthread_join(*(unpthread_t + 1), NULL);

    sem_destroy(&g_sem);

    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    Test_Mutex();
    return 0;
}