// Linux命名管道通信（任意进程之间）
// 命名管道通信：使用mkfifo系统函数创建一个FIFO文件，对该文件进行读写，实现进程间通信

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#define __USE_BSD
#include <unistd.h>

#define FIFO_PATH "/tmp/03_NamedPipeTest.txt"

int Test_Write(const char *_Arg)
{
    int nReadFd = open(FIFO_PATH, O_WRONLY);
    if (nReadFd == -1)
        perror("open failed.\n");

    while (1)
    {
        write(nReadFd, _Arg, strlen(_Arg));

        sleep(1);
    }

    return 1;
}

int Test_Read(void)
{
    char chBuf[513] = {0};

    if (mkfifo(FIFO_PATH, 0644) == -1 && errno == EEXIST)
        perror("mkfifo failed.\n");

    int nReadFd = open(FIFO_PATH, O_RDONLY);
    if (nReadFd == -1)
        perror("open failed.\n");

    while (1)
    {
        memset(chBuf, 0, sizeof(chBuf));
        read(nReadFd, chBuf, sizeof(chBuf) - 1);

        if (chBuf[0] != '\0')
            printf("Read：%s\n", chBuf);
    }

    return 1;
}

// 具有亲缘关系之间的通信测试
int Test02(void)
{
    int nRtn = fork();

    if (nRtn == 0) // 子进程
    {
        Test_Read();
    }
    else if (nRtn > 0)
    {
        usleep(1000);
        int nRtnChildStatus = 0;

        Test_Write("Hello world.");
        wait(&nRtnChildStatus);
    }
    else
        perror("fork failed.\n");

    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
#ifdef TEST01
    // 任意进程之间的通信
    if (argc >= 2)
    {
        if (argv[1][0] == '0')
            Test_Read();
        else if (argc >= 3)
        {
            if (argv[1][0] == '1')
                Test_Write(argv[2]);
            else
            {
                perror("传入命令行参数错误.\n");
                return 1;
            }
        }

        perror("传入命令行参数错误.\n");
        return 1;
    }
#else
    Test02();

#endif

    return 0;
}