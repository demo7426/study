//进程关系，获取进程ID、进程组ID、会话ID，设置进程组ID、会话ID
//在使用shell命令控制进程时，不能去修改进程组ID、会话ID

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

//打印当前进程ID、进程组ID、会话ID信息
void Printf_CurProcessMsg(void)
{
    pid_t gid = getpgrp();          //获取当前进程组ID
    pid_t ppid = getppid();         //获取父进程ID
    pid_t pgid = getpgid(0);        //获取父进程组ID
    pid_t sid = getsid(0);          //获取会话ID

    printf("gid = %ld, ppid = %ld, pgid = %ld, sid =%ld\n", gid, ppid, pgid, sid);
}

int main(int argc, char *argv[], char *envp[])
{
    Printf_CurProcessMsg();
    if (setpgid(0, getppid()) == -1)//设置进程组ID
    {
        perror("Setpgid error.");
    }
    
    pid_t nNewSidID = setsid();//设置会话ID
    if (nNewSidID == -1)
    {
        perror("Setpgid error.");
    }

    printf("The new sidid = &ld\n", nNewSidID);
    Printf_CurProcessMsg();
    pause();

    return 0;
}