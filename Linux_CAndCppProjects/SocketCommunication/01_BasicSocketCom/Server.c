
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

//服务器
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

    struct sockaddr_in tsockaddr_in_Client;
    socklen_t unSize = 0;
    int nClientFd = accept(nServerFd, (struct sockaddr *)&tsockaddr_in_Client, &unSize);
    if (nClientFd == -1)
    {
        close(nServerFd);
        perror("accept failed.\n");
        return -1;
    }

    char chBuf[257] = { 0 };
    while (1)
    {
        memset(chBuf, 0, sizeof(chBuf));

        int nRecvLength = recv(nClientFd, chBuf, sizeof(chBuf) - 1, 0);

        if (nRecvLength > 0)
        {
            printf("Server recv：%s\n", chBuf);
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
    close(nServerFd);

    return 0;
}

int main(int argc, char *argv[], char *envp)
{
    ServerFunc();
    return 0;
}