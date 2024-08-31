// select多线程模型
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

typedef struct _FD_INFO
{
    int Fd;
    int *MaxFd;
    fd_set *tfd_set;
} FD_INFO, *PFD_INFO;

pthread_mutex_t g_MutexFd_Info;

// 接收新的客户端的连接
void *ThreadAccept(void *_Arg)
{
    PFD_INFO pFd_Info = (PFD_INFO)_Arg;

    struct sockaddr_in tsockaddr_in_Client;
    socklen_t unSize = 0;
    int nClientFd = accept(pFd_Info->Fd, (struct sockaddr *)&tsockaddr_in_Client, &unSize);
    if (nClientFd == -1)
    {
        close(pFd_Info->Fd);
        perror("accept failed.\n");
        return -1;
    }

    pthread_mutex_lock(&g_MutexFd_Info);
    *pFd_Info->MaxFd = *pFd_Info->MaxFd > nClientFd ? *pFd_Info->MaxFd : nClientFd;
    FD_SET(nClientFd, pFd_Info->tfd_set);
    pthread_mutex_unlock(&g_MutexFd_Info);

    free(pFd_Info);
    pFd_Info = NULL;
    return NULL;
}

void *ThreadCommunication(void *_Arg)
{
    PFD_INFO pFd_Info = (PFD_INFO)_Arg;
    int nClientFd = pFd_Info->Fd;
    char chBuf[257] = {0};

    memset(chBuf, 0, sizeof(chBuf));

    int nRecvLength = recv(nClientFd, chBuf, sizeof(chBuf) - 1, 0);

    if (nRecvLength > 0)
    {
        printf("%s\n", chBuf);
        if (send(nClientFd, "Server recv success.", sizeof("Server recv success."), 0) == -1)
        {
            perror("send failed.\n");
        }
    }
    else if (nRecvLength == 0)
    {
        printf("客户端断开连接.\n");

        pthread_mutex_lock(&g_MutexFd_Info);
        FD_CLR(nClientFd, pFd_Info->tfd_set);
        pthread_mutex_unlock(&g_MutexFd_Info);

        close(nClientFd);
    }
    else
    {
        perror("recv failed.\n");
    }

    free(pFd_Info);
    pFd_Info = NULL;
    return NULL;
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

    pthread_mutex_init(&g_MutexFd_Info, NULL);
    while (1)
    {
        fd_set tReadfd_set = tfd_set;
        int nRtn = select(nMaxfd + 1, &tReadfd_set, NULL, NULL, NULL); // select第一个参数为最大的文件描述符+1
        if (nRtn == -1)
        {
            perror("select failed.\n");
        }

        // 处理客户端连接
        if (FD_ISSET(nServerFd, &tReadfd_set))
        {
            pthread_t tid;
            PFD_INFO pFd_Info = (PFD_INFO)malloc(sizeof(FD_INFO));
            if (pFd_Info == NULL)
            {
                perror("malloc failed.\n");
            }

            pFd_Info->Fd = nServerFd;
            pFd_Info->MaxFd = &nMaxfd;
            pFd_Info->tfd_set = &tfd_set;

            pthread_create(&tid, NULL, ThreadAccept, pFd_Info);
            pthread_detach(tid);
        }

        // 处理通信
        for (int i = 0; i <= nMaxfd; i++)
        {
            if (i != nServerFd && FD_ISSET(i, &tReadfd_set))
            {
                pthread_t tid;
                PFD_INFO pFd_Info = (PFD_INFO)malloc(sizeof(FD_INFO));
                if (pFd_Info == NULL)
                {
                    perror("malloc failed.\n");
                }

                pFd_Info->Fd = i;
                pFd_Info->MaxFd = &nMaxfd;
                pFd_Info->tfd_set = &tfd_set;

                pthread_create(&tid, NULL, ThreadCommunication, pFd_Info);
                pthread_detach(tid);
            }
        }
    }

    pthread_mutex_destroy(&g_MutexFd_Info);
    close(nServerFd);

    return 0;
}

int main(int argc, char *argv[], char *envp[])
{
    SelectServer();

    return 0;
}