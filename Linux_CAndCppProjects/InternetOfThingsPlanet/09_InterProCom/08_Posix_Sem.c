// Linux有名信号量通信（任意进程之间）  Posix类型 用于进程同步
// 一共5个API，分别为：sem_open、sem_wait、sem_post、sem_close、sem_unlink
// sem_open；打开或创建一个相对于 /dev/shm/ 路径的信号量文件
// sem_wait：申请一个信号量
// sem_post：增加一个信号量
// sem_close：关闭信号量
// sem_unlink：删除信号量文件

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <semaphore.h>
#include <unistd.h>

#define FILEPATH "08_Posix_Sem.txt"

int main(int argc, char *argv[], char *envp[])
{
    if (argc < 2)
    {
        perror("缺少传入的命令行参数.\n");
        return -1;
    }

    sem_t *pusem_t = sem_open(FILEPATH, O_CREAT | O_RDWR, 0644, 0);
    if (pusem_t == SEM_FAILED)
    {
        perror("sem_open failed.\n");
        return -1;
    }

    switch (atoi(argv[1]))
    {
    case 0: // 申请信号量
        while (1)
        {
            sem_wait(pusem_t);
            printf("成功申请信号量\n");
        }

        break;
    case 1: // 增加信号量
        while (1)
        {
            sem_post(pusem_t);
            printf("成功增加信号量\n");
            sleep(1);
        }

        break;
    case 2: // 删除信号量集、信号量文件
        sem_close(pusem_t);
        sem_unlink(FILEPATH);
        break;
    default:
        break;
    }

    return 0;
}
