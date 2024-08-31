
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "ThreadPool.h"

THREADPOOL_INFO* g_ptThreadPool_Info = NULL;

void ThreadCommunication(void *_Arg)
{
    int nClientFd = (int)_Arg;
    char chBuf[257] = { 0 };
    while (1)
    {
        memset(chBuf, 0, sizeof(chBuf));

        int nRecvLength = recv(nClientFd, chBuf, sizeof(chBuf) - 1, 0);

        if (nRecvLength > 0)
        {
            printf("%s\n", chBuf);
            if (send(nClientFd, "Server recv success.", sizeof("Server recv success."), 0) == -1)
            {
                perror("send failed.\n");
                break;
            }
            
        }
        else if (nRecvLength == 0)
        {
            printf("客户端断开连接.\n");
            break;
        }
        else
        {
            perror("recv failed.\n");
            break;
        }
    }

    close(nClientFd);
}

void SocketAccept(void *_Arg)
{
    int nServerFd = (int)_Arg;
    while (1)
    {
        struct sockaddr_in tsockaddr_in_Client;
        socklen_t unSize = 0;
        int nClientFd = accept(nServerFd, (struct sockaddr *)&tsockaddr_in_Client, &unSize);
        if (nClientFd == -1)
        {
            close(nServerFd);
            perror("accept failed.\n");
            return -1;
        }
        ThreadPoolAdd(g_ptThreadPool_Info, ThreadCommunication, (void*)nClientFd);
    }
    close(nServerFd);
}

int SelectServer(void)
{
    int nServerFd = socket(AF_INET, SOCK_STREAM, 0);
    if (nServerFd == -1)
    {
        perror("socket failed.\n");
        return -1;
    }
    
    struct sockaddr_in tsockaddr_in;
    tsockaddr_in.sin_family = AF_INET;
    tsockaddr_in.sin_port = htons(9998);
    tsockaddr_in.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY：0.0.0.0

    if (bind(nServerFd, (const struct sockaddr *)&tsockaddr_in, sizeof(struct sockaddr_in)) == -1)
    {
        close(nServerFd);
        perror("bind failed.\n");
        return -1;
    }
    
    //同一时刻listen内部最大监听数为128，内核决定的
    if (listen(nServerFd, 128) == -1)
    {
        close(nServerFd);
        perror("listen failed.\n");
        return -1;
    }

    g_ptThreadPool_Info = ThreadPool_Create(3, 8, 100);
    ThreadPoolAdd(g_ptThreadPool_Info, SocketAccept, (void*)nServerFd);

    //pthread_exit(0);
    pause();

    return 0;
}

int main(int argc, char *argv[], char *envp[])
{
    SelectServer();

    return 0;
}