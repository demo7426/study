//Linux 线程互斥量
//一共4个API，分别为pthread_mutex_init、pthread_mutex_destroy、pthread_mutex_lock、pthread_mutex_unlock

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int g_nNum = 20000;
pthread_mutex_t g_mutex;

void *THreadFunc01(void *_Arg)
{
    while (1)
    {
        pthread_mutex_lock(&g_mutex);

        if (g_nNum == 0)
        {
            pthread_mutex_unlock(&g_mutex);
            break;
        }
            

        if (g_nNum > 0)
            g_nNum--;
        else
            g_nNum++;    
        printf("THreadFunc01:%ld\n", g_nNum);
        sleep(1);
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
            break;
        }
        
        if (g_nNum > 0)
            g_nNum--;
        else
            g_nNum++;    
        printf("THreadFunc02:%ld\n", g_nNum);
        sleep(1);
        pthread_mutex_unlock(&g_mutex);
    }
    return NULL;
}

int Test_Mutex(void)
{
    pthread_t unpthread_t[2];

    pthread_mutex_init(&g_mutex, NULL);

    pthread_create(unpthread_t, NULL, THreadFunc01, NULL);
    pthread_create(unpthread_t + 1, NULL, THreadFunc02, NULL);

    pthread_join(*unpthread_t, NULL);
    pthread_join(*(unpthread_t + 1), NULL);

    pthread_mutex_destroy(&g_mutex);

    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    Test_Mutex();
    return 0;
}