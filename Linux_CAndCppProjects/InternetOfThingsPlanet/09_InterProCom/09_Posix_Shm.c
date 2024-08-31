// Linux共享内存通信（任意进程之间）  Posix类型 用于进程同步
// 一共5个API，分别为：shm_open、ftruncate、mmap、munmap、shm_unlink
// shm_open；打开或创建一个相对于 /dev/shm/ 路径的共享内存文件
// ftruncate：申请一个信号量
// sem_post：增加一个信号量
// sem_close：关闭信号量
// sem_unlink：删除信号量文件

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <semaphore.h>
#include <string.h>

#define __USE_BSD
#include <unistd.h>

#define SEMFILEPATH "08_Posix_Sem.txt"
#define SHMFILEPATH "09_Posix_Shm.txt"

int main(int argc, char *argv[], char *envp[])
{
    if (argc < 2)
    {
        perror("缺少传入的命令行参数.\n");
        return -1;
    }

    sem_t *pusem_t = sem_open(SEMFILEPATH, O_CREAT | O_RDWR, 0644, 0);
    if (pusem_t == SEM_FAILED)
    {
        perror("sem_open failed.\n");
        return -1;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    int nShmFd = shm_open(SHMFILEPATH, O_CREAT | O_RDWR, 0644);
    if (nShmFd == -1)
    {
        perror("shm_open failed.\n");
        return -1;
    }

    if (ftruncate(nShmFd, 4096) == -1)
    {
        perror("ftruncate failed.\n");
        return -1;
    }

    void *pvShmAddr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, nShmFd, 0);
    if (pvShmAddr == MAP_FAILED)
    {
        perror("mmap failed.\n");
        return -1;
    }

    ////////////////////////////////////////////////////////////////////////////////////

    switch (atoi(argv[1]))
    {
    case 0: // 读取共享内存数据
        while (1)
        {
            sem_wait(pusem_t);
            printf("%s\n", pvShmAddr);
        }

        break;
    case 1: // 写入共享内存数据
    {
        int nFreq = 0;
        memset(pvShmAddr, 0, 4096);
        while (1)
        {
            usleep(500000);//保证读取比写入更快打印出数据
            sprintf(pvShmAddr, "%ld", nFreq++);
            usleep(500000);
            sem_post(pusem_t);
        }
    }

    break;
    case 2: // 删除信号量集、信号量文件
        sem_close(pusem_t);
        sem_unlink(SEMFILEPATH);

        munmap(pvShmAddr, 4096);
        shm_unlink(SHMFILEPATH);
        puts("删除成功");
        break;
    default:
        break;
    }

    return 0;
}
