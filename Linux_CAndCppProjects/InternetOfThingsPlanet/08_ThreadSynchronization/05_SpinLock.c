//Linux 线程自旋锁
//一共4个API，分别为pthread_spin_init、pthread_spin_destroy、pthread_spin_lock、pthread_spin_unlock

#include <stdio.h>
#include <stdlib.h>
#define __USE_XOPEN2K
#include <pthread.h>
#include <unistd.h>

int g_nNum = 20000;
pthread_spinlock_t g_spin;

void *THreadFunc01(void *_Arg)
{
    while (1)
    {
        pthread_spin_lock(&g_spin);

        if (g_nNum == 0)
        {
            pthread_spin_unlock(&g_spin);
            break;
        }
            

        if (g_nNum > 0)
            g_nNum--;
        else
            g_nNum++;    
        printf("THreadFunc01:%ld\n", g_nNum);
        pthread_spin_unlock(&g_spin);
    }
    

    return NULL;
}

void *THreadFunc02(void *_Arg)
{
    while (1)
    {
        pthread_spin_lock(&g_spin);

        if (g_nNum == 0)
        {
            pthread_spin_unlock(&g_spin);
            break;
        }
        
        if (g_nNum > 0)
            g_nNum--;
        else
            g_nNum++;    
        printf("THreadFunc02:%ld\n", g_nNum);

        sleep(1);
        pthread_spin_unlock(&g_spin);
        
    }
    return NULL;
}

int Test_spin(void)
{
    pthread_t unpthread_t[2];

    pthread_spin_init(&g_spin, 0);

    pthread_create(unpthread_t, NULL, THreadFunc01, NULL);
    pthread_create(unpthread_t + 1, NULL, THreadFunc02, NULL);

    pthread_join(*unpthread_t, NULL);
    pthread_join(*(unpthread_t + 1), NULL);

    pthread_spin_destroy(&g_spin);

    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    Test_spin();
    return 0;
}