//Linux 线程读写锁
//一共若干个API，分别为pthread_rwlockattr_init、pthread_rwlock_destroy、
//                 pthread_rwlock_rdlock、pthread_rwlock_wrlock、pthread_rwlock_trywrlock、pthread_rwlock_timedwrlock、pthread_rwlock_unlock、
//设置读写锁属性    pthread_rwlockattr_init、pthread_rwlockattr_setkind_np、pthread_rwlockattr_destroy

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define __USE_UNIX98
#include <pthread.h>

int g_nNum = 0;
pthread_rwlock_t g_rwlock;

void *THreadReadFunc(void *_Arg)
{
    while (1)
    {
        pthread_rwlock_rdlock(&g_rwlock);
        printf("THreadReadFunc:%ld\n", g_nNum);
        pthread_rwlock_unlock(&g_rwlock);
    }
    
    return NULL;
}

void *THreadwriteFunc(void *_Arg)
{
    while (1)
    {
        pthread_rwlock_wrlock(&g_rwlock);
        g_nNum++;
        printf("THreadwriteFunc:%ld\n", g_nNum);
        pthread_rwlock_unlock(&g_rwlock);
        //sleep(1);
    }
    return NULL;
}

int Test_Mutex(void)
{
    pthread_t unpthread_t[2];
    pthread_rwlockattr_t rwlockAttr;

    pthread_rwlockattr_init(&rwlockAttr);
    pthread_rwlockattr_setkind_np(&rwlockAttr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);//设置读写锁写优先级高于读优先级(默认为读优先级高于写优先级)
    pthread_rwlock_init(&g_rwlock, &rwlockAttr);

    pthread_create(unpthread_t, NULL, THreadReadFunc, NULL);
    pthread_create(unpthread_t + 1, NULL, THreadwriteFunc, NULL);

    pthread_join(*unpthread_t, NULL);
    pthread_join(*(unpthread_t + 1), NULL);

    pthread_rwlock_destroy(&g_rwlock);
    pthread_rwlockattr_destroy(&rwlockAttr);
    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    Test_Mutex();
    return 0;
}