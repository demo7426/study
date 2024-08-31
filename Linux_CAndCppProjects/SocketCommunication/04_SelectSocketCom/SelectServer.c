//select基础模型
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

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
    tsockaddr_in.sin_port = htons(10000);
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

    int nMaxfd = nServerFd;
    fd_set tfd_set;
    FD_ZERO(&tfd_set);
    FD_SET(nServerFd, &tfd_set);

    while (1)
    {
        fd_set tReadfd_set = tfd_set;
        int nRtn = select(nMaxfd + 1, &tReadfd_set, NULL, NULL, NULL);//select第一个参数为最大的文件描述符+1
        if (nRtn == -1)
        {
            perror("select failed.\n");
        }

        //处理客户端连接
        if (FD_ISSET(nServerFd, &tReadfd_set))
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

            nMaxfd = nMaxfd > nClientFd ? nMaxfd : nClientFd;
            FD_SET(nClientFd, &tfd_set);
        }

        //处理通信
        for (int i = 0; i <= nMaxfd; i++)
        {
            if (i != nServerFd && FD_ISSET(i, &tReadfd_set))
            {
                printf("nMaxfd = %ld, nClientFd = %ld\n", nMaxfd, i);
                int nClientFd = i;
                char chBuf[257] = {0};

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
                    FD_CLR(i, &tfd_set);
                    close(i);
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

    close(nServerFd);

    return 0;
}

int main(int argc, char *argv[], char *envp[])
{
    SelectServer();

    return 0;
}