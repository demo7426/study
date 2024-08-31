//Linux 线程与信号之间的关系
//线程之间共享 线程处理函数、共享信号未决队列；私有 私有信号未决队列、线程私有屏蔽信号集
//一共有7个API函数，分别为：kill、sigqueue、tkill、tgkill、pthread_kill、pthread_sigqueue、pthread_sigmask
//kill、sigqueue：发送信号到共享信号未决队列
//tkill、tgkill、pthread_kill、pthread_sigqueue：发送信号到私有信号未决队列
//pthread_sigmask：线程私有屏蔽信号集

#define _POSIX_C_SOURCE 199309L  // 定义 POSIX 版本为 1993 年标准
#include <stdio.h>
#include <stdlib.h>
//#define __USE_GNU
#include <pthread.h>
#define __USE_POSIX199506
#include <sys/types.h>
#include <sys/syscall.h>
#define __USE_BSD
//#define __USE_POSIX
#include <unistd.h>

#include <signal.h>

void SignalFunc(int _Arg)
{
    printf("SignalFunc called, signal = %ld\n", _Arg);
}

void *ThreadFunc(void *_Arg)
{
    sigset_t tsigset_t;

    sigemptyset(&tsigset_t);
    sigaddset(&tsigset_t, SIGINT);

    pthread_sigmask(SIG_BLOCK, &tsigset_t, NULL);
    sleep(4);
    printf("ThreadFunc called.\n");
    
    
    return NULL;
}

int Test_ThreadSignal(void)
{
    pthread_t unpthread_t;

    signal(SIGINT, SignalFunc);//线程之间共享线程处理函数

    if (pthread_create(&unpthread_t, NULL, ThreadFunc, NULL) != 0)
        perror("pthread_create failed.\n");

    usleep(1000000);
    //kill(getpid(), SIGINT);
    pthread_kill(unpthread_t, SIGINT);

    // union sigval tsigval;
    // tsigval.sival_int = 1234;
    // pthread_sigqueue(unpthread_t, SIGINT, tsigval);

    pthread_join(unpthread_t, NULL);
    
    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    Test_ThreadSignal();
    return 0;
}
