//Linux 线程（轻量级进程）基本操作
//一共5个API，分别为：pthread_create、pthread_attr_init、pthread_attr_setstacksize、pthread_attr_setdetachstate、pthread_attr_destroy
//pthread_create：第一个参数为struct pthread的首地址，结构体内部包含了线程id等信息

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

char g_chBuf[13] = "进入线程";

//只写了一部分的内容，更详细的代码查看Linux源码
struct pthread
{
    char ch[0x2d0];
    pid_t pid;
};


void* Thread_PrinfMsg(void *_Arg)
{
    printf("%s\n", (char*)_Arg);
    
    pthread_exit(0);
}

//打印线程ID
int Test_PrintfThreadID(void)
{
    pthread_t ulpthread_t = 0;//pthread_t为struct pthread首地址
    pthread_attr_t tpthread_attr_t;

    pthread_attr_init(&tpthread_attr_t);
    pthread_attr_setstacksize(&tpthread_attr_t, 16 * 1024 * 1024);//设置栈大小
    
    //设置线程连接属性，默认为join
    //如果设置为分离属性，防止线程访问到已经被释放的内存空间
    pthread_attr_setdetachstate(&tpthread_attr_t, PTHREAD_CREATE_DETACHED);

    if (pthread_create(&ulpthread_t, &tpthread_attr_t, Thread_PrinfMsg, g_chBuf))
    {
        perror("pthread_create failed.\n");
        return 0;
    }

    printf("线程id = %ld\n", ((struct pthread*)ulpthread_t)->pid);

    //pthread_join(ulpthread_t, NULL);
    pthread_attr_destroy(&tpthread_attr_t);
    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    Test_PrintfThreadID();
    return 0;
}