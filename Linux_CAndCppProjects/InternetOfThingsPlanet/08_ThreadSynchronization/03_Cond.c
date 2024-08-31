//Linux 线程条件变量
//一共6个API，分别为pthread_cond_init、pthread_cond_destroy、pthread_cond_wait、pthread_cond_timedwait、pthread_cond_signal、pthread_cond_broadcast
//pthread_cond_wait、pthread_cond_timedwait：条件变量等待
//pthread_cond_signal、pthread_cond_broadcast：唤醒等待的条件变量

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM 5

int g_nNum = NUM;
pthread_mutex_t g_mutex;
pthread_cond_t g_cond;

void *THreadFunc01(void *_Arg)
{
    while (1)
    {
        pthread_mutex_lock(&g_mutex);
        
        while (g_nNum != 0)//防止线程被虚假唤醒（pthread_cond_wait接收到信号时，g_nNum != 0可能不满足条件）
        {
            pthread_cond_wait(&g_cond, &g_mutex);
            printf("THreadFunc01:%ld\n", g_nNum);
        }
        g_nNum = NUM;
    
        pthread_mutex_unlock(&g_mutex);
    }
    

    return NULL;
}

void *THreadFunc02(void *_Arg)
{
    while (1)
    {
        pthread_mutex_lock(&g_mutex);

        if (g_nNum == 0)
        {
            pthread_mutex_unlock(&g_mutex);
            pthread_cond_signal(&g_cond);
            continue;
        }
        
        if (g_nNum > 0)
            g_nNum--;
        else
            g_nNum++;    
        printf("THreadFunc02:%ld\n", g_nNum);
        pthread_mutex_unlock(&g_mutex);
    }
    return NULL;
}

int Test_Mutex(void)
{
    pthread_t unpthread_t[2];

    pthread_mutex_init(&g_mutex, NULL);
    pthread_cond_init(&g_cond, NULL);

    pthread_create(unpthread_t, NULL, THreadFunc01, NULL);
    pthread_create(unpthread_t + 1, NULL, THreadFunc02, NULL);

    pthread_join(*unpthread_t, NULL);
    pthread_join(*(unpthread_t + 1), NULL);

    pthread_mutex_destroy(&g_mutex);
    pthread_cond_destroy(&g_cond);

    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    Test_Mutex();
    return 0;
}