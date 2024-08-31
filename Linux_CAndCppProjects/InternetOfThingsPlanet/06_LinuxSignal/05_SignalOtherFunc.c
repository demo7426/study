//信号的其它相关函数
//一共有5个API函数，分别为sigprocmask、sigismember、alarm、abort、psignal函数
//alarm：设置一个定时器，在一段时间后将 SIGALRM 信号发送给当前进程
//abort： 产生一个 SIGABRT 信号给当前进程,导致程序异常终止并生成一个core dump文件
//psignal：打印某个信号默认输出终端信息

#define _POSIX_C_SOURCE 199309L  // 定义 POSIX 版本为 1993 年标准
#include <stdio.h>
#include <stdlib.h>
#define __USE_BSD
#include <unistd.h>
#define __USE_POSIX
#define __USE_MISC
#include <signal.h>

//测试sigprocmask、sigismember函数
int Test01(void)
{
    sigset_t tsigset_t;
    sigemptyset(&tsigset_t);
    sigaddset(&tsigset_t, SIGINT);

    sigprocmask(SIG_BLOCK, &tsigset_t, NULL);//屏蔽信号集，和sigsuspend区别是该函数不会等待信号触发
    while (1)
    {
        for (int i = 1; i < _NSIG; i++)
        {
            if (sigismember(&tsigset_t, i))//获取当前被阻塞的、未决的信号集
            {
                printf("%ld 信号处于未决信号集.\n", i);
            }
        }
        
        sleep(1);
    }
    
}

void Printf_Msg(int _Arg)
{
    printf("Printf_Msg called signal is %ld\n", _Arg);

    signal(SIGALRM, Printf_Msg);
}

int Test02(void)
{
    signal(SIGALRM, Printf_Msg);
    
    while (1)
    {
        alarm(1);//设置一个定时器，在一段时间后将 SIGALRM 信号发送给当前进程
        sleep(1);
    }
}

int Test03(void)
{
    sleep(2);
    abort();//产生一个 SIGABRT 信号给当前进程,导致程序异常终止并生成一个core dump文件
}

int Test04(void)
{
    for (int i = 1; i < _NSIG; i++)
    {
       psignal(i, "Signal 信息：");//打印某个信号默认输出终端信息
    }
}

int main(int argc, char *argv[], char *envp[])
{
    Test04();
    return 0;
}