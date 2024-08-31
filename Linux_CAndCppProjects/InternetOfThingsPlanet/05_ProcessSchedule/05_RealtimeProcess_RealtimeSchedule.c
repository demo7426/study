//测试实时任务（SCHED_FIFO、SCHED_RR）、普通任务CPU占用情况
//对于单核来说实时任务最多占用95%的资源，剩下的5%给普通任务，防止普通任务被饿死

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define __USE_GNU            
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char *argv[], char *envp[])
{
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);    
    sched_setaffinity(getpid(), sizeof(set), &set);//设置CPU亲和力

    if (argc < 3)
    {
        perror("传入命令行参数个数最少为3个.\n");
        return EXIT_FAILURE;
    }
    
    struct sched_param tsched_param = { atoi(argv[2]) };
    if (sched_setscheduler(getpid(), atoi(argv[1]), &tsched_param))
        perror("sched_setscheduler failed.\n"); 

    while (1)
    {
        /* code */
    }
    

    return EXIT_SUCCESS;
}

