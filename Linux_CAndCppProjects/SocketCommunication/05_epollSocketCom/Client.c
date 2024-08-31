
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *ThreadRead(void *_Arg)
{
    int nClientFd = (int)_Arg;
    char chBuf[257] = {0};

    while (1)
    {
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
    }

    return NULL;
}

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
    tsockaddr_in.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &(tsockaddr_in.sin_addr.s_addr));

    if (connect(nClientFd, (const struct sockaddr *)&tsockaddr_in, sizeof(struct sockaddr_in)) == -1)
    {
        close(nClientFd);
        perror("bind failed.\n");
        return -1;
    }

    char chBuf[257] = {0};
    int nFreq = 0;
    pthread_t tid;

    pthread_create(&tid, NULL, ThreadRead, (void*)nClientFd);
    pthread_detach(tid);

    while (1)
    {
        sprintf(chBuf, "Hello world. %ld\n", nFreq++ % 2000);
        if (send(nClientFd, chBuf, sizeof(chBuf), 0) == -1)
        {
            perror("send failed.\n");
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