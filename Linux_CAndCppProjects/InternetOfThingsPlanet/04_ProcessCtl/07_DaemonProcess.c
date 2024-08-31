//创建守护进程（精灵进程）

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define _BSD_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
//创建守护进程
int CreateDaemonProcess()
{
    int nFork = fork();

    if (nFork == 0)
    {
        int nSid = setsid();
        if (nSid == -1)
            perror("Setsid Called is failed.\n");
        
        int nChildFork = fork();
        if (nChildFork == 0)
        {
            if (chdir("/") == -1)
                perror("Chdir Called is failed.\n");
            
            umask(0);

            int nFd = open("/dev/null", O_RDWR);
            if (nFd == -1)
                perror("Open Called is failed.\n");
            
            dup2(nFd, 0);
            dup2(nFd, 1);
            dup2(nFd, 2);

            close(nFd);
            signal(SIGCHLD, SIG_IGN);
            puts("1");
        }
        else if (nChildFork > 0)
            exit(EXIT_SUCCESS);
        else
            perror("Fork Called is failed.\n");
    }
    else if (nFork > 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
        perror("Fork Called is failed.\n");
    

    return EXIT_SUCCESS;
}

void WriteFile(void)
{
    int nFd = open("/tmp/07_DaemonProcess.txt", O_RDWR | O_CREAT |O_TRUNC, 0644);
    if (nFd == -1)
        perror("Open Called is failed.\n");

    char chBuf[513] = { 0 }; 
    time_t lTimeValue = 0;
    while (1)
    {
        memset(chBuf, 0, sizeof(chBuf));
        if (time(&lTimeValue) == -1)
            perror("Time Called is failed.\n");
        
        sprintf(chBuf, "%s\n", ctime(&lTimeValue));
        write(nFd, chBuf, sizeof(chBuf) - 1);

        sleep(1);
    }
    close(nFd); 
}

int main(int argc, char *acrgv[], char *envp[])
{
    CreateDaemonProcess();
    //daemon(0, 0); //需要加上 #define _BSD_SOURCE 定义
    WriteFile();
    return 0;
}
