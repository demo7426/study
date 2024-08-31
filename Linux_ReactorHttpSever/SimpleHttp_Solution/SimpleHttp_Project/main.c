#include "Server.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
    /*if (argc < 3)
    {
        perror("Please input: exec port path.\n");
        return -1;
    }*/

    //切换程序的工作目录
    chdir(("/home/qianrui/HttpSource"));

    int nServerFd = InitListenFd(10000);
    if (nServerFd == -1)
    {
        perror("InitListenFd failed.\n"); 
        return -1;
    }

    if (EpollRun(nServerFd) == -1)
    {
        perror("EpollRun failed.\n");
        return -1;
    }

    return 0;
}