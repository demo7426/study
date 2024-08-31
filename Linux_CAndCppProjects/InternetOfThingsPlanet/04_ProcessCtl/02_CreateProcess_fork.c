#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TEST_FILEPATH "02_CreateProcess_fork.txt"

static int g_nValue = 100;

static void Test01()
{
    // 创建一个新的子进程，调用一次返回两次；
    //   拥有写时拷贝技术（只有在需要写入数据时，才分配给子进程新的物理内存，不然只分配虚拟内存、与父进程共享物理内存）;
    //   父子进程共享struct inod信息,文件指针也是共享的
    //   父进程：返回子进程PID；
    //   子进程：返回0；
    //   失败：返回-1。
    int nRtnFork = fork();

    int nValue = 100;
    int *pnValue = (int *)malloc(sizeof(int));
    *pnValue = 100;

    int nFd = open(TEST_FILEPATH, O_CREAT | O_RDWR, 0644);
    if (nFd == -1)
        perror("Open file failed.\n");
    
    if (nRtnFork == 0)
    {
        char chBuf[257] = {0};
        lseek(nFd, 0, SEEK_SET);
        read(nFd, chBuf, sizeof(chBuf) - 1);
        printf("Read msg：%s\n", chBuf);

        // 当写入数据时，系统会立即给子进程分配一个新的物理内存，并且将父进程的数据拷贝过来
        g_nValue = 99;
        nValue = 99;
        *pnValue = 99;

        printf("Children process id = %ld\n", getpid());
        printf("Children：g_nValue = %ld, nValue = %ld, *pnValue = %ld\n", g_nValue, nValue, *pnValue);
        free(pnValue);
        close(nFd);
    }
    else if (nRtnFork > 0)
    {
        write(nFd, "123456789", 9);

        printf("Parent process id = %ld, fork() id = %ld\n", getpid(), nRtnFork);
        printf("Parent：g_nValue = %ld, nValue = %ld, *pnValue = %ld\n", g_nValue, nValue, *pnValue);

        free(pnValue);
        close(nFd);
    }
    else
        perror("fork error.");
}

int main(int argc, char *argv[], char *envp[])
{
    Test01();
    return 0;
}
