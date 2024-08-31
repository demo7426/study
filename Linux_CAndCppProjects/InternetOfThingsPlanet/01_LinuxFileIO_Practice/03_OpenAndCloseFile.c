//Linux文件IO，打开、创建或关闭文件（使用这套系统API不能跨平台）
//一共有四个API函数，分别为opne、openat(先打开目录再打开文件)、create、close

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define FILEPATH "OpenAndCloseFile.txt"

void Test_Open(void)
{
    int nFd = open(SEMFILEPATH, O_RDWR | O_CREAT | O_TRUNC, 0777);//创建文件的初始权限会 0777&umask(默认值为0022) 为最终权限
    if (nFd == -1)
    {
        perror("Open file failed.");
    }
    close(nFd);
}

void Test_Create(void)
{
    int nFd = creat(SEMFILEPATH, 0666);
    if (nFd == -1)
    {
        perror("Creat file failed.");
    }
    close(nFd);
}

void Test_Openat(void)
{
    int nDirFd = open("./", O_RDONLY);
    if (nDirFd == -1)
    {
        perror("Open file failed.");
    }

    int nOpenatFd = openat(nDirFd, SEMFILEPATH, O_RDONLY | O_CREAT, 0777);
    if (nOpenatFd == -1)
    {
        perror("Openat file failed.");
        close(nDirFd);
    }

    close(nDirFd);
    close(nOpenatFd);
}

int main(int argc, char* argv[])
{
    Test_Openat();
    return 0;
}

