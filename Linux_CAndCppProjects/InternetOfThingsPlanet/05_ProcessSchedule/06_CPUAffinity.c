//设置、获取进程或线程的CPU亲和力
//一共两个API：sched_setaffinity、sched_getaffinity

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define __USE_GNU
#include <sched.h>
#include <errno.h>

int main(int argc, char *argv[], char *envp[])
{
    cpu_set_t tcpu_set_t;
    CPU_ZERO(&tcpu_set_t);

    for (size_t i = 0; i < 2; i++)
    {
        CPU_SET(i, &tcpu_set_t);
    }
    
    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &tcpu_set_t) == -1)//设置CPU亲和力
    {
       if (errno != 0)
       {
            perror("sched_setscheduler failed.\n");
            return EXIT_FAILURE;
       }
    } 
    
    CPU_ZERO(&tcpu_set_t);
    if (sched_getaffinity(getpid(), sizeof(tcpu_set_t), &tcpu_set_t))//获取CPU亲和力
    {
        perror("sched_getaffinity failed.\n"); 
        return EXIT_FAILURE;
    }
    
    printf("亲和的CPU编号为：");
    for (size_t i = 0; i < sizeof(tcpu_set_t); i++)
    {
        if (CPU_ISSET(i, &tcpu_set_t))//对内容进行判定
        {
            printf("%ld ", i);
        }
        
    }
    puts("");

    while (1)
    {
        sleep(1);
    }
    

    return EXIT_SUCCESS;
}
