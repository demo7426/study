//Linux文件同步（使用这套系统API不能跨平台）
//一共有三个API函数，分别为sync、fsync、fdatasync

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define FILEPATH "05_FileSync.txt"

void Test_Sync(void)
{
    int nFd = open(SEMFILEPATH, O_RDWR | O_CREAT | O_TRUNC, 0777);//创建文件的初始权限会 0777&umask(默认值为0022) 为最终权限
    if (nFd == -1)
    {
        perror("Open file failed.");
    }

    const char chBuf[] = "Hello world.\n";

    write(nFd, chBuf, sizeof(chBuf));
    sync();
    //close(nFd);
}

int main(int argc, char* argv[])
{
    Test_Sync();
    return 0;
}

