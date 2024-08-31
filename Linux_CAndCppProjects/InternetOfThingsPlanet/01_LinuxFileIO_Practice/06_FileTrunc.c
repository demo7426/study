//Linux文件截断，可以理解为重定义文件大小（使用这套系统API不能跨平台）
//一共有两个API函数，分别为ftruncate、truncate
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

const char* g_chFilePath = "06_FileTrunc.txt";

void Printf_CurFileOffset(int _Fd)
{
    printf("CurOffset: %ld\n", lseek(_Fd, 0, SEEK_CUR));
}

void Test_Ftruncate(void)
{
    int nFd = open(g_chFilePath, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (nFd == -1)
        perror("Open file failed.\n");
    Printf_CurFileOffset(nFd);

    const char chBuf[] = "Hello world.\n";
    write(nFd, chBuf, sizeof(chBuf));
    Printf_CurFileOffset(nFd);

    ftruncate(nFd, 3);
    Printf_CurFileOffset(nFd);
    close(nFd);
}


void Test_Truncate(void)
{
    int nFd = open(g_chFilePath, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (nFd == -1)
        perror("Open file failed.\n");
    Printf_CurFileOffset(nFd);

    const char chBuf[] = "Hello world.\n";
    write(nFd, chBuf, sizeof(chBuf));
    Printf_CurFileOffset(nFd);

    truncate(g_chFilePath, 5);
    Printf_CurFileOffset(nFd);
    close(nFd);
}

int main(int argc, char *argv[])
{
    Test_Truncate();
    return 0;
}
