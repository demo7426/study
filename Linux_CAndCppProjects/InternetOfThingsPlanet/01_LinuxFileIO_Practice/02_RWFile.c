//Linux文件IO，读写文件（使用这套系统API不能跨平台）
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void Printf_CurFilePos(int _Fd)
{
    off_t lOffset = lseek(_Fd, 0, SEEK_CUR);
    printf("Current offset is %u\n", lOffset);
}

void Test01(void)
{
    int fd = open("02_RWFile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        perror("File open fail.");
    
    char chBuf[256] = { 0 };
    Printf_CurFilePos(fd);
    memset(chBuf, 'a', sizeof(chBuf));
    write(fd, chBuf, 100);
    Printf_CurFilePos(fd);

    lseek(fd, 10, SEEK_SET);
    Printf_CurFilePos(fd);
    read(fd, chBuf, 40);
    Printf_CurFilePos(fd);
    
    memset(chBuf, 'b', sizeof(chBuf));
    write(fd, chBuf, 20);
    Printf_CurFilePos(fd);

    memset(chBuf, 0, sizeof(chBuf));
    lseek(fd, 0, SEEK_SET);
    read(fd, chBuf, 100);
    printf("%s\n", chBuf);

    close(fd);
}

int main(int argc, char* argv[])
{
    Test01();
    return 0;
}