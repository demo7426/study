
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// 客户端
int ClientFunc(void)
{
    int nClientFd = socket(AF_INET, SOCK_STREAM, 0);
    if (nClientFd == -1)
    {
        perror("socket failed.\n");
        return -1;
    }

    struct sockaddr_in tsockaddr_in;
    tsockaddr_in.sin_family = AF_INET;
    tsockaddr_in.sin_port = htons(10000);
    inet_pton(AF_INET, "127.0.0.1", &(tsockaddr_in.sin_addr.s_addr));

    if (connect(nClientFd, (const struct sockaddr *)&tsockaddr_in, sizeof(struct sockaddr_in)) == -1)
    {
        close(nClientFd);
        perror("bind failed.\n");
        return -1;
    }

    char chBuf[257] = {0};
    while (1)
    {
        
        memset(chBuf, 0, sizeof(chBuf));
        scanf("%s", chBuf);
        if (send(nClientFd, chBuf, sizeof(chBuf), 0) == -1)
        {
            perror("send failed.\n");
            break;
        }

        memset(chBuf, 0, sizeof(chBuf));
        int nRecvLength = recv(nClientFd, chBuf, sizeof(chBuf) - 1, 0);
        if (nRecvLength > 0)
        {
            printf("Client recv：%s\n", chBuf);
        }
        else if (nRecvLength == 0)
        {
            printf("客户端断开链接\n");
        }
        else
        {
            perror("recv failed.\n");
            break;
        }

        sleep(1);
    }

    close(nClientFd);

    return 0;
}

int main(int argc, char *argv[], char *envp)
{
    ClientFunc();
    return 0;
}