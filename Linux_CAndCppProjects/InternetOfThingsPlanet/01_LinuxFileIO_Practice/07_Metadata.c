// Linux获取文件元数据信息（使用这套系统API不能跨平台）
// 一共有三个API函数，分别为stat（只能获取源文件元数据）、fstat、lstat（可以获取链接文件元数据）
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define FILEPATH "07_Metadata.txt"

// 打印元数据信息
void Printf_Stat(struct stat _Stat)
{
    printf("st_dev:%ld, st_ino = %ld, st_nlink = %ld\n", _Stat.st_dev, _Stat.st_ino, _Stat.st_nlink);
}

void Test_Stat(void)
{
    struct stat tStat;
    stat(SEMFILEPATH, &tStat);
    Printf_Stat(tStat);
}

void Test_Fstat(void)
{
    struct stat tStat;
    int nOpenFd = open(SEMFILEPATH, O_RDONLY);
    if (nOpenFd == -1)
        perror("Open file failed.\n");

    fstat(nOpenFd, &tStat);
    Printf_Stat(tStat);

    close(nOpenFd);
}

void Test_Lstat(void)
{
    struct stat tStat;
    lstat(SEMFILEPATH, &tStat);
    Printf_Stat(tStat);
}

int main(int argc, char *argv[])
{
    int nCreateFd = creat(SEMFILEPATH, 0644);
    if (nCreateFd == -1)
        perror("Creat file failed.\n");
    
    Test_Lstat();

    close(nCreateFd);

    return 0;
}
