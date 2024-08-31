#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define __USE_UNIX98
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

struct _PEOPLE_INFO
{
    char Names[20];
    int Age;
};

struct _LIST_INFO
{
    int Num;
    struct _LIST_INFO *Next;
};

int g_nNum = 0;
pthread_mutex_t g_mutexCalNum;
pthread_rwlock_t g_mutexRW;                 //读写锁
pthread_cond_t g_condIsEmpty;               //条件变量
sem_t g_semProduct, g_semConsume;           //信号量
struct _LIST_INFO* g_ptListHead = NULL;     //链表头节点

void* ThreadFuncCalled(void* _Arg)
{
    struct _PEOPLE_INFO* tPeople_Info = (struct _PEOPLE_INFO*)_Arg;

    memset(tPeople_Info->Names, 0, sizeof(tPeople_Info->Names));
    strcpy(tPeople_Info->Names, "Meixi");
    tPeople_Info->Age = 36;

    for (int i = 0; i < 5; i++)
    {
        printf("子线程：ThreadFuncCalled %d\n", i);
    }
    
    pthread_exit(_Arg);//线程退出函数可以传递参数到上一级线程

    return NULL;
}

//pthread_join 线程阻塞及回收资源
void Test01(void)
{
    struct _PEOPLE_INFO tPeople_Info;
    pthread_t thID;
    pthread_create(&thID, NULL, ThreadFuncCalled, &tPeople_Info);

    for (int i = 0; i < 5; i++)
    {
        printf("主线程：Test01 %d\n", i);
    }
    //sleep(3);
    //pthread_exit(NULL);//当pthread_exit在主线程退出时，只释放自己线程的资源，不会释放其它线程的资源

    void* pvValue= NULL;
    pthread_join(thID, &pvValue);//线程回收函数阻塞当前线程，可接收子线程退出时返回的数据，及回收分配给子线程的寄存器资源
    printf("子线程ID = %ld,返回：Names = %s, Age = %d\n", 
            thID, ((struct _PEOPLE_INFO*)pvValue)->Names, ((struct _PEOPLE_INFO*)pvValue)->Age);
    pthread_exit(NULL);
}

//pthread_detach 线程分离
void Test02(void)
{
    struct _PEOPLE_INFO tPeople_Info;
    pthread_t thID;
    pthread_create(&thID, NULL, ThreadFuncCalled, &tPeople_Info);

    for (int i = 0; i < 5; i++)
    {
        printf("主线程：Test01 %d\n", i);
    }

    pthread_detach(thID);
    pthread_exit(NULL);//这里调用会直接会回收掉进程资源
}

void* ThreadFuncCalled_CalNum_01(void* _Arg)
{
    for (int i = 0; i < 50; i++)
    {
        pthread_mutex_lock(&g_mutexCalNum);
        /* code */
        printf("ThreadFuncCalled_CalNum_01：%ld\n", ++g_nNum);
        pthread_mutex_unlock(&g_mutexCalNum);

        usleep(10);
    }

    pthread_exit(NULL);
    return NULL;
}

void* ThreadFuncCalled_CalNum_02(void* _Arg)
{
    for (int i = 0; i < 50; i++)
    {
        pthread_mutex_lock(&g_mutexCalNum);
        /* code */
        printf("ThreadFuncCalled_CalNum_02：%ld\n", ++g_nNum);
        pthread_mutex_unlock(&g_mutexCalNum);

        usleep(10);
    }

    pthread_exit(NULL);
    return NULL;
}

//mutex互斥锁 测试
void Test03(void)
{
    pthread_t thIDs[2];
    pthread_mutex_init(&g_mutexCalNum, NULL);

    pthread_create(thIDs, NULL, ThreadFuncCalled_CalNum_01, NULL);
    pthread_create(thIDs + 1, NULL, ThreadFuncCalled_CalNum_02, NULL);

    pthread_join(thIDs[0], NULL);
    pthread_join(thIDs[1], NULL);

    pthread_mutex_destroy(&g_mutexCalNum);
}

void* Test04_RdFunc(void* _Arg)
{
    for (int i = 0; i < 50; i++)
    {
        /* code */
        pthread_rwlock_rdlock(&g_mutexRW);
        printf("Read thread：%u, %ld\n",pthread_self(),  g_nNum);
        pthread_rwlock_unlock(&g_mutexRW);

        usleep(10);
    }

    pthread_exit(NULL);
    
    return NULL;
}

void* Test04_WrFunc(void* _Arg)
{
    for (int i = 0; i < 50; i++)
    {
        /* code */
        pthread_rwlock_wrlock(&g_mutexRW);
        printf("Write thread：%u, %ld\n",pthread_self(),  ++g_nNum);
        pthread_rwlock_unlock(&g_mutexRW);
    }

    pthread_exit(NULL);
    
    return NULL;
}

//读写锁测试(与互斥锁的区别是读写锁可以多个线程同时获取读锁)
void Test04(void)
{
    pthread_t thRdIDs[5];//读线程ID
    pthread_t thWrIDs[3];//写线程ID
    pthread_rwlock_init(&g_mutexRW, NULL);

    for (int i = 0; i < sizeof(thRdIDs) / sizeof(thRdIDs[0]); i++)
    {
        /* code */
        pthread_create(thRdIDs + i, NULL, Test04_RdFunc, NULL);
    }
    
    for (int i = 0; i < sizeof(thWrIDs) / sizeof(thWrIDs[0]); i++)
    {
        /* code */
        pthread_create(thWrIDs + i, NULL, Test04_WrFunc, NULL);
    }   

    for (int i = 0; i < sizeof(thRdIDs) / sizeof(thRdIDs[0]); i++)
         pthread_join(thRdIDs[i], NULL);
        
    for (int i = 0; i < sizeof(thWrIDs) / sizeof(thWrIDs[0]); i++)
        pthread_join(thWrIDs[i], NULL);

    pthread_rwlock_destroy(&g_mutexRW);
}

void *ProductFunc(void *_Arg)
{
    while (1)
    {
        pthread_mutex_lock(&g_mutexCalNum);
        /* code */
        struct _LIST_INFO* ptList = (struct _LIST_INFO*)malloc(sizeof(struct _LIST_INFO));
        
        //头插数据节点
        ptList->Num = rand() % 1000;
        ptList->Next = g_ptListHead;
        g_ptListHead = ptList;

        printf("This product threadID is %u, num = %ld\n", pthread_self(), ptList->Num);
        pthread_mutex_unlock(&g_mutexCalNum);
        pthread_cond_signal(&g_condIsEmpty);
        sleep(rand() % 3);
    }

     pthread_exit(NULL);

    return NULL;
}

void *ConsumeFunc(void *_Arg)
{
    while (1)
    {
        /* code */
        pthread_mutex_lock(&g_mutexCalNum);

        while (g_ptListHead == NULL)
        {
            /* code */
            pthread_cond_wait(&g_condIsEmpty, &g_mutexCalNum);
        }
        

        struct _LIST_INFO* ptList = g_ptListHead;
        printf("This consume threadID is %u, num = %ld\n", pthread_self(), ptList->Num);

        pthread_mutex_unlock(&g_mutexCalNum);
        sleep(rand() % 3);
    }

    pthread_exit(NULL);

    return NULL;
}

//条件变量 测试
void Test05()
{
    pthread_t thProductID[3];           //生产者线程ID
    pthread_t thConsumeID[5];           //消费者线程ID

    pthread_mutex_init(&g_mutexCalNum, NULL);
    pthread_cond_init(&g_condIsEmpty, NULL);

    for (int i = 0; i < sizeof(thProductID) / sizeof(thProductID[0]); i++)
        pthread_create(thProductID + i, NULL, ProductFunc, NULL);
    for (int i = 0; i < sizeof(thConsumeID) / sizeof(thConsumeID[0]); i++)
        pthread_create(thConsumeID + i, NULL, ConsumeFunc, NULL);

    for (int i = 0; i < sizeof(thProductID) / sizeof(thProductID[0]); i++)
        pthread_join(thProductID[i], NULL);
    for (int i = 0; i < sizeof(thConsumeID) / sizeof(thConsumeID[0]); i++)
        pthread_join(thConsumeID[i], NULL);

    pthread_mutex_destroy(&g_mutexCalNum);
    pthread_cond_destroy(&g_condIsEmpty);
}

void *ProductFunc_Sem(void *_Arg)
{
    while (1)
    {
        sem_wait(&g_semProduct);
        pthread_mutex_lock(&g_mutexCalNum);
        /* code */
        struct _LIST_INFO* ptList = (struct _LIST_INFO*)malloc(sizeof(struct _LIST_INFO));
        
        //头插数据节点
        ptList->Num = rand() % 1000;
        ptList->Next = g_ptListHead;
        g_ptListHead = ptList;

        printf("This product threadID is %u, num = %ld\n", pthread_self(), ptList->Num);
        pthread_mutex_unlock(&g_mutexCalNum);

        sem_post(&g_semConsume);
        sleep(rand() % 3);
    }

     pthread_exit(NULL);

    return NULL;
}

void *ConsumeFunc_Sem(void *_Arg)
{
    while (1)
    {
        /* code */
        sem_wait(&g_semConsume);
        pthread_mutex_lock(&g_mutexCalNum);

        struct _LIST_INFO* ptList = g_ptListHead;
        printf("This consume threadID is %u, num = %ld\n", pthread_self(), ptList->Num);

        pthread_mutex_unlock(&g_mutexCalNum);
        sem_post(&g_semProduct);
        
        sleep(rand() % 3);
    }

    pthread_exit(NULL);

    return NULL;
}

//信号量 测试
void Test06()
{
    pthread_t thProductID[3];           //生产者线程ID
    pthread_t thConsumeID[5];           //消费者线程ID

    pthread_mutex_init(&g_mutexCalNum, NULL);
    sem_init(&g_semProduct, 0, 6);
    sem_init(&g_semConsume, 0, 0);

    for (int i = 0; i < sizeof(thProductID) / sizeof(thProductID[0]); i++)
        pthread_create(thProductID + i, NULL, ProductFunc_Sem, NULL);
    for (int i = 0; i < sizeof(thConsumeID) / sizeof(thConsumeID[0]); i++)
        pthread_create(thConsumeID + i, NULL, ConsumeFunc_Sem, NULL);

    for (int i = 0; i < sizeof(thProductID) / sizeof(thProductID[0]); i++)
        pthread_join(thProductID[i], NULL);
    for (int i = 0; i < sizeof(thConsumeID) / sizeof(thConsumeID[0]); i++)
        pthread_join(thConsumeID[i], NULL);

    pthread_mutex_destroy(&g_mutexCalNum);
    sem_destroy(&g_semProduct);
    sem_destroy(&g_semConsume);
}

int main()
{
    //Test01();
    //Test02();
    Test06();
    return 0;
}