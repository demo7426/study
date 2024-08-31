//Linux线程基础操作2
//一共4个API，分别为：pthread_self、pthread_detach、pthread_join、pthread_exit
//pthread_self：返回当前线程标识符
//pthread_detach：线程分离
//pthread_join：等待指定线程返回
//pthread_exit：线程显示退出

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

struct pThread
{
    char chBuf[0x2d0];
    pid_t tid;
};

pid_t gettid(void)
{
return syscall(SYS_gettid);
}

void *ThreadFunc(void *_Arg)
{
    //sleep(2);

    pthread_t ulThreadIdentify = pthread_self();//返回当前线程标识符

    printf("子线程id = %ld, 子线程id = %ld, 子线程组(进程id)id = %ld\n", ((struct pThread*)ulThreadIdentify)->tid, gettid(), getpid());
 
    pthread_exit("子线程返回数据");//字符串常量数据放在代码段，不用担心内存被子线程释放的问题
    return NULL;
}

int Test01()
{
    pthread_t ulThreadIdentify;

    pthread_create(&ulThreadIdentify, NULL, ThreadFunc, NULL);
    //pthread_detach(ulThreadIdentify);//线程分离

    printf("子线程id = %ld, 主线程id = %ld, 主线程组(进程id)id = %ld\n", ((struct pThread*)ulThreadIdentify)->tid, gettid(), getpid());

    char *chBuf;//指针不能
    pthread_join(ulThreadIdentify, &chBuf);//等待指定线程返回
    printf("线程返回的值为：%s\n", chBuf);
    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    Test01();
    return 0;
}