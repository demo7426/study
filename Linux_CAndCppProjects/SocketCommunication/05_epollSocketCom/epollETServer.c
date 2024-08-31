// epoll通信机制（边沿模式触发）
// 一共有3个API，分别为epoll_create、epoll_wait、epoll_ctl

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>

// 服务器
int ServerFunc(void)
{
    int nServerFd = socket(AF_INET, SOCK_STREAM, 0);
    if (nServerFd == -1)
    {
        perror("socket failed.\n");
        return -1;
    }

    struct sockaddr_in tsockaddr_in;
    tsockaddr_in.sin_family = AF_INET;
    tsockaddr_in.sin_port = htons(9999);
    tsockaddr_in.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY：0.0.0.0

    if (bind(nServerFd, (const struct sockaddr *)&tsockaddr_in, sizeof(struct sockaddr_in)) == -1)
    {
        close(nServerFd);
        perror("bind failed.\n");
        return -1;
    }

    // 同一时刻listen内部最大监听数为128，内核决定的
    if (listen(nServerFd, 128) == -1)
    {
        close(nServerFd);
        perror("listen failed.\n");
        return -1;
    }

    int nEpFd = epoll_create(1);
    if (nEpFd == -1)
    {
        close(nServerFd);
        perror("epoll_create failed.\n");
        return -1;
    }

    struct epoll_event tepoll_event;
    tepoll_event.events = EPOLLIN | EPOLLET;
    tepoll_event.data.fd = nServerFd;

    epoll_ctl(nEpFd, EPOLL_CTL_ADD, nServerFd, &tepoll_event);

    struct epoll_event tepoll_events[1024];
    while (1)
    {
        int nEventSize = sizeof(tepoll_events) / sizeof(tepoll_events[0]);
        for (int i = 0; i < nEventSize; i++)
            tepoll_events[i].data.fd = -1;

        if (epoll_wait(nEpFd, tepoll_events, nEventSize, -1) > 0)
        {
            for (int i = 0; i < nEventSize; i++)
            {
                if (tepoll_events[i].data.fd == -1)
                    continue;

                if (tepoll_events[i].data.fd == nServerFd) // 处理连接的情况
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

                    // 将文件描述符的读写变成非阻塞模式
                    int nFlag = fcntl(nClientFd, F_GETFL);
                    nFlag |= O_NONBLOCK;
                    fcntl(nClientFd, F_SETFL, nFlag);

                    tepoll_event.events = EPOLLIN | EPOLLET;
                    tepoll_event.data.fd = nClientFd;
                    epoll_ctl(nEpFd, EPOLL_CTL_ADD, nClientFd, &tepoll_event);
                }
                else // 处理数据通信的情况
                {
                    char chBuf[6] = {0};

                    while (1)
                    {
                        memset(chBuf, 0, sizeof(chBuf));

                        int nRecvLength = recv(tepoll_events[i].data.fd, chBuf, sizeof(chBuf) - 1, 0);

                        if (nRecvLength > 0)
                        {
                            printf("%s", chBuf);
                            
                        }
                        else if (nRecvLength == 0)
                        {
                            printf("客户端断开连接.\n");
                            epoll_ctl(nEpFd, EPOLL_CTL_DEL, tepoll_events[i].data.fd, &tepoll_event);
                            close(tepoll_events[i].data.fd);
                            break;
                        }
                        else
                        {
                            if (errno == EAGAIN)//处理读缓冲区数据为空情况
                            {
                                if (send(tepoll_events[i].data.fd, "Server recv success.", sizeof("Server recv success."), 0) == -1)
                                {
                                    perror("send failed.\n");
                                    break;
                                }
                                break;
                            }
                            else
                            {
                                perror("recv failed.\n");
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    epoll_ctl(nEpFd, EPOLL_CTL_DEL, nServerFd, &tepoll_event);
    close(nServerFd);

    return 0;
}

int main(int argc, char *argv[], char *envp)
{
    ServerFunc();
    return 0;
}