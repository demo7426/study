// Linux无名管道通信（有亲缘关系的进程之间才可以）

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// 无名管道父子进程通信测试
int Test_AnonymousPipe_01()
{
    int nPipes[2] = {0}; // nPipesp[0]--读管道，nPipes[1]--写管道
    pipe(nPipes);

    int nRtn = fork();
    if (nRtn == 0) // 子进程
    {
        close(nPipes[0]);

        while (1)
        {
            write(nPipes[1], "Hello world.", strlen("Hello world."));
            sleep(1);
        }
    }
    else if (nRtn > 0) // 父进程
    {
        char chReadBuf[513] = {0};
        close(nPipes[1]);

        while (1)
        {
            memset(chReadBuf, 0, sizeof(chReadBuf));
            read(nPipes[0], chReadBuf, sizeof(chReadBuf) - 1);
            printf("Read：%s\n", chReadBuf);
            sleep(1);
        }
    }
    else
        perror("fork failed.\n");

    return 1;
}

// 无名管道兄弟进程通信测试
int Test_AnonymousPipe_02()
{
    int nPipes[2] = {0}; // nPipesp[0]--读管道，nPipes[1]--写管道
    pipe(nPipes);

    int nRtn = fork();
    if (nRtn == 0) // 子进程
    {
        close(nPipes[0]);

        while (1)
        {
            write(nPipes[1], "Hello world.", strlen("Hello world."));
            sleep(1);
        }
    }
    else if (nRtn > 0) // 父进程
    {
        char chReadBuf[513] = {0};
        close(nPipes[1]);

        int nRet = fork(); // 子进程
        if (nRet == 0)
        {
            while (1)
            {
                memset(chReadBuf, 0, sizeof(chReadBuf));
                read(nPipes[0], chReadBuf, sizeof(chReadBuf) - 1);
                printf("Read：%s\n", chReadBuf);
                sleep(1);
            }
        }
        else if (nRet > 0) // 父进程
        {
            /* code */
        }
        else
            perror("fork failed.\n");
    }
    else
        perror("fork failed.\n");

    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    Test_AnonymousPipe_02();
    return 0;
}