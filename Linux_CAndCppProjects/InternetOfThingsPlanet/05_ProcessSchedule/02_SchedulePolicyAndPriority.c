//在Linux下设置进程的调度策略、优先级
//一共有6个API接口
//sched_setscheduler：设置调度策略及实时任务优先级，不能设置普通任务的优先级
//sched_getscheduler：获取进程调度策略
//sched_setparam：设置实时任务的优先级
//sched_getparam：获取实时任务的优先级
//setpriority：设置普通任务的优先级
//getpriority：获取普通任务的优先级

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

//设置实时任务的优先级，实时优先级范围为0~99，值越大优先级越高
int Test_SetRealtimeTask(void)
{
    //可在 /proc目录下查看动态优先级
    //当当前进程为实时任务时，动态优先级 = 99 - 实时优先级
    int nScheduler = -1;
    struct sched_param tsched_param = { 80 };

    //设置调度策略及进程优先级
    //sched_setscheduler设置优先级，仅在sched_setscheduler设置为实时任务时有效，若sched_setscheduler设置为普通任务则传入优先级必须为0，否则函数调用失败
    if (sched_setscheduler(getpid(), SCHED_RR, &tsched_param))
        perror("sched_setscheduler failed.\n");

    nScheduler = sched_getscheduler(getpid());              //获取进程调度策略
    if (nScheduler == -1)
        perror("sched_getscheduler failed.\n");
    
    tsched_param.__sched_priority = 0;
    sched_getparam(getpid(), &tsched_param);                //获取实时任务的优先级
    printf("重新设置优先级之前：进程 %ld 的调度策略为：%ld, 实时任务优先级为：%ld\n", getpid(), nScheduler, tsched_param.__sched_priority);

    tsched_param.__sched_priority = 60;
    if (sched_setparam(getpid(), &tsched_param) == -1)      //设置实时任务的优先级
        perror("sched_setparam failed.\n");
    
    tsched_param.__sched_priority = 0;
    sched_getparam(getpid(), &tsched_param);                //获取实时任务的优先级
    printf("重新设置优先级之后：进程 %ld 的调度策略为：%ld, 实时任务优先级为：%ld\n", getpid(), nScheduler, tsched_param.__sched_priority);

    return EXIT_SUCCESS;
}

int Test_OrdinaryTask(void)
{
    //可在 /proc目录下查看动态优先级
    //当当前进程为普通任务时，动态优先级 = 120 + nice值
    int nScheduler = -1;
    int nNice = 0;
    struct sched_param tsched_param = { 0 };

    //设置调度策略及进程优先级
    //sched_setscheduler设置优先级，仅在sched_setscheduler设置为实时任务时有效，若sched_setscheduler设置为普通任务则传入优先级必须为0，否则函数调用失败
    if (sched_setscheduler(getpid(), SCHED_OTHER, &tsched_param))
        perror("sched_setscheduler failed.\n");

    nScheduler = sched_getscheduler(getpid());              //获取进程调度策略
    if (nScheduler == -1)
        perror("sched_getscheduler failed.\n");
    
    nNice = getpriority(PRIO_PROCESS, getpid());            //获取普通任务的优先级
    if (nNice == -1)
    {
        printf("errno = %ld\n", errno);
    }
    
    printf("重新设置优先级之前：进程 %ld 的调度策略为：%ld, 普通任务优先级nice为：%ld\n", getpid(), nScheduler, nNice);

    if (setpriority(PRIO_PROCESS, getpid(), 10))            //设置普通任务的优先级
        perror("setpriority failed.\n");
    
    nNice = getpriority(PRIO_PROCESS, getpid());            //获取普通任务的优先级
    if (nNice == -1)
    {
        printf("errno = %ld\n", errno);
    }
    
    printf("重新设置优先级之后：进程 %ld 的调度策略为：%ld, 普通任务优先级nice为：%ld\n", getpid(), nScheduler, nNice);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[], char *envp[])
{
    Test_OrdinaryTask();
    pause();
    return 0;
}


