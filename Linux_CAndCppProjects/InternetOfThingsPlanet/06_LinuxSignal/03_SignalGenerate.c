//Linux信号产生测试
//一共3个API函数，分别为raise（向当前进程发送信号）、kill（向对应的进程发送单个信号）、sigqueue（向对应的进程发送单个信号及附加信息）

#define _POSIX_C_SOURCE 199309L  // 定义 POSIX 版本为 1993 年标准
#include <stdio.h>
#define __USE_BSD
#include <unistd.h>
#define __USE_POSIX
#include <signal.h>


void Printf_Signal(int _Arg)
{
    printf("signal:%ld\n", _Arg);

    if (signal(SIGINT, Printf_Signal) == SIG_ERR)//将SIGINT信号安装到Printf_Msg函数
    {
        perror("signal failed.\n");
        return;
    }
}

void Printf_Sigaction(int _Arg)
{
    printf("Printf_Sigaction:%ld\n", _Arg);
   
    struct sigaction tsigaction;
    tsigaction.sa_handler = Printf_Sigaction;

    if (sigaction(SIGINT, &tsigaction, NULL) ==-1)
    {
        perror("sigaction failed.\n");
        return;
    }
}

void Printf_sa_sigaction (int _SigalNum, siginfo_t *_Info, void *_Context)
{
    printf("Printf_sa_sigaction:%ld, sa_flags = %ld\n", _SigalNum, _Info->si_int);

    struct sigaction tsigaction;
    tsigaction.sa_flags |= SA_SIGINFO;//SA_SIGINFO 调用带有三个参数而不是一个参数的信号捕获函数。
    tsigaction.sa_sigaction = Printf_sa_sigaction;

    if (sigaction(SIGINT, &tsigaction, NULL) ==-1)
    {
        perror("sigaction failed.\n");
        return;
    }
}

//signal信号注册函数测试
int Test_Signal(void)
{
    if (signal(SIGINT, Printf_Signal) == SIG_ERR)
    {
        perror("signal failed.\n");
        return 0;
    }
    
    while (1)
    {
        sleep(1);

        kill(getpid(), SIGINT);
    }
    
    return 1;
}

//sigaction信号注册函数测试
//使用sa_handler进行简单安装，功能和signal安装类似
//使用sa_sigaction进行复杂安装，在简易安装的基础上增加了两个新的形参
int Test_Sigaction(void)
{
    struct sigaction tsigaction;
    //tsigaction.sa_handler = Printf_Sigaction;
    tsigaction.sa_flags |= SA_SIGINFO;
    tsigaction.sa_sigaction = Printf_sa_sigaction;

    if (sigaction(SIGINT, &tsigaction, NULL) ==-1)
    {
        perror("sigaction failed.\n");
        return 0;
    }

    union sigval usigval;
    usigval.sival_int = 12345;
    
    while (1)
    {
        sleep(1);

        sigqueue(getpid(), SIGINT, usigval);
    }
}

int main(int argc, char *argv[], char *envp[])
{
    Test_Sigaction();
    return 0;
}
