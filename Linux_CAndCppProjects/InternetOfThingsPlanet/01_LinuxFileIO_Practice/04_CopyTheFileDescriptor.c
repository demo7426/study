//Linux 复制文件描述符，文件描述符:输出到控制台的文件描述符默认为1（使用这套系统API不能跨平台）
//一共有三个API函数，分别为dup、dup2、dup3

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static const char* g_chFilePath = "CopyTheFileDescriptor.txt";

void Test_Dup(void)
{
    int nFd_01 = open(g_chFilePath, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (nFd_01 == -1)
        perror("Open file fail.");
    
    int nFd_02 = dup(1);
    if (nFd_02 == -1)
        perror("Dup(1) fail.");
    
    close(1);
    int nFd_03 = dup(nFd_01);//默认分配最小的文件描述符
    if (nFd_03 == -1)
        perror("Dup(nFd_01) fail.");

    printf("fd = %ld\n", nFd_03);
}

void Test_Dup2(void)
{
    int nFd_01 = open(g_chFilePath, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (nFd_01 == -1)
        perror("Open file fail.");
    
    int nFd_02 = dup2(1, nFd_01 + 1);//防止关闭正在使用的文件描述符
    if (nFd_02 == -1)
        perror("Dup(1) fail.");
    
    close(1);
    int nFd_03 = dup2(nFd_01, 1);
    if (nFd_03 == -1)
        perror("Dup(nFd_01) fail.");

    printf("fd = %ld\n", nFd_03);
}

void Test_Dup3(void)
{
    int nFd_01 = open(g_chFilePath, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (nFd_01 == -1)
        perror("Open file fail.");
    
    int nFd_02 = dup3(1, nFd_01 + 1, 0);//防止关闭正在使用的文件描述符
    if (nFd_02 == -1)
        perror("Dup(1) fail.");
    
    close(1);
    int nFd_03 = dup3(nFd_01, 1, 0);
    if (nFd_03 == -1)
        perror("Dup(nFd_01) fail.");

    printf("fd = %ld\n", nFd_03);
}

int main(int argc, char argv[])
{
    Test_Dup3();
    return 0;
}
