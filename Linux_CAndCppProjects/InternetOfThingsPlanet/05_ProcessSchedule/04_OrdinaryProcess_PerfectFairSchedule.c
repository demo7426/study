//普通进程，完全公平调度
#include <stdlib.h>
#include <stdio.h>
#define __USE_GNU            
#include <sched.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

//普通进程，完全公平调度测试
int Test_OrdinaryProcess_PerfectFairSchedule(void)
{
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    sched_setaffinity(getpid(), sizeof(set), &set);//设置CPU亲和力

    __pid_t nPid = fork();

    if (nPid == 0)//子进程
    {
        setpriority(PRIO_PROCESS, getpid(), -5);//设置普通任务优先级
    }
    else if (nPid > 0)//父进程
    {
        setpriority(PRIO_PROCESS, getpid(), 5);
    }
    else
        perror("fork failed.\n");

    while (1)
    {
        /* code */
    }
    
}

int main(int argc, char* argv[], char* envp[])
{
    Test_OrdinaryProcess_PerfectFairSchedule();
    return EXIT_SUCCESS;
}


