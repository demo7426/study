// 自己实现system函数

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int My_System(const char *_Command)
{
    if (!_Command)
        return -1;

    int nPid = fork();
    if (nPid == 0) // 子进程
    {
        execl("/bin/sh", "sh", "-c", _Command, NULL);
        _exit(127);
    }
    else if (nPid > 0) // 父进程
    {
        int nStatus = 0;
        if (waitpid(nPid, &nStatus, 0) > 0)
        {
            if (errno == ECHILD)
                printf("没有子进程需要等待.\n");
            else
            {
                printf("子进程ID = %ld退出, 退出码 = %d, 是否正常退出 = %d\n", nPid, WEXITSTATUS(nStatus), WIFEXITED(nStatus));
                return 0;
            }
        }
    }
    else
    {
        perror("fork failed.\n");
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    if (argc <= 1)
    {
        perror("需要传入最少一个命令行参数.\n");
        return 0;
    }

    My_System(argv[1]);

    return 0;
}
