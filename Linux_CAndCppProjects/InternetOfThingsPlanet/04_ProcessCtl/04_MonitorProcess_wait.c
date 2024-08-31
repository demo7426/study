// 等待子进程返回
// 两个API函数，分别为wait,waitpid

#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

// 创建一个进程，使用wait函数
void Test01(void)
{
    int nPid = fork();

    if (nPid == 0) // 子进程
    {
        printf("Children process start.\n");
        _exit(2);
    }
    else if (nPid > 0) // 父进程
    {
        printf("Parent process start.\n");

        int nStatus = 0;
        __pid_t nRtn = wait(&nStatus);
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

// 创建一个进程，使用waitpid函数
void Test02(void)
{
    int nPid = fork();

    if (nPid == 0) // 子进程
    {
        printf("Children process start.\n");
        _exit(2);
    }
    else if (nPid > 0) // 父进程
    {
        printf("Parent process start.\n");

        kill(nPid, SIGSTOP); // 向一个线程发出stop信号
        int nStatus = 0;
        __pid_t nRtn = waitpid(nPid, &nStatus, WUNTRACED); // WUNTRACED如果子进程被暂停则返回其暂停状态
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

// 创建10个进程，waitpid回收子进程
void Test03(void)
{
    int nProcessCount = 10; // 进程数量

    for (int i = 0; i < nProcessCount; i++)
    {
        int nPid = fork();

        if (nPid == 0) // 子进程
        {
            printf("Children process start.\n");
            _exit(i);
        }
        else if (nPid > 0) // 父进程
        {
            printf("Parent process start.\n");

            int nStatus = 0;
            __pid_t nRtn = waitpid(nPid, &nStatus, WUNTRACED); // WUNTRACED如果子进程被暂停则返回其暂停状态
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
}

int main(int argc, char *argv[], char *envp[])
{
    Test03();
    return 0;
}