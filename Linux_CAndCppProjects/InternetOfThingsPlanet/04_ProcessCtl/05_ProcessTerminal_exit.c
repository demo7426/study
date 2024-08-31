//进程退出函数
//一共三个API、一个return关键字，exit、retrun、_exit,atexit
// exit、return功能一样：当前目录下查看./05_ProcessTerminal_exit.png图片信息
// atexit函数 注册用户的退出函数只针对自己当前的进程,在其它进程无法该进程的用户注册的退出函数
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>       
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void Clear01(void)
{
    puts("Clear01 called.");
}

void Clear02(void)
{
    puts("Clear02 called.");
}

int Test01(void)
{
    atexit(Clear01);
    atexit(Clear02);
    //_exit(0);
    exit(0);
    //return 0;
}

int Test02(void)
{
    int nPID = fork();

    if (nPID == 0)
    {
        atexit(Clear01);
        atexit(Clear02);
        printf("Children process start.\n");
        exit(0);
    }
    else if (nPID > 0)
    {
        int nStatus = 0;
        printf("Parent process start.\n");

        pid_t nRtn = waitpid(nPID, &nStatus, WCONTINUED);
        if (nRtn > 0)
        {
            printf("子进程ID = %ld退出, 退出码 = %d, 是否正常退出 = %d\n", nRtn, WEXITSTATUS(nStatus), WIFEXITED(nStatus));
        }
        else if (nRtn == -1)
        {
            if (errno == ECHILD)
                printf("没有子进程需要等待.\n");
            else
                perror("wait failed.\n");
        }

    }
    else
        perror("Fork failed.\n");
}

int main(int argc, char *argv[], char *envp[])
{
    Test02();

    _exit(0);
}

