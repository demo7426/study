//信号等待函数
//一共3个API，分别为
//pause：等待所有信号
//sigsuspend：屏蔽信号集（屏蔽信号集合）
//sigwait：等待信号集（等待信号集合）

#define _POSIX_C_SOURCE 199309L  // 定义 POSIX 版本为 1993 年标准
#include <stdio.h>
#define __USE_BSD
#include <unistd.h>
#define __USE_POSIX
#include <signal.h>

//signal信号注册函数测试
int Test_SignalWait(void)
{
    while (1)
    {
        //pause();

        sigset_t tsigset_t;
        sigemptyset(&tsigset_t);
        sigaddset(&tsigset_t, SIGQUIT);

        //sigsuspend(&tsigset_t);//屏蔽信号集

        int nSigNum = 0;
        sigwait(&tsigset_t, &nSigNum);//sigwait 可以返回触发信号类型
        printf("Access signal：%ld.\n", nSigNum);

        usleep(1000);
    }
    
    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    Test_SignalWait();
    return 0;
}



