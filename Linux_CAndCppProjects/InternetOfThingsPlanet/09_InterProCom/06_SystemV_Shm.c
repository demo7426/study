// Linux进程间通信共享内存及信号量测试  System V类型
// 一共3个API，分别为：shmget、shmat、shmctl
// shmget：计算共享内存标识符ID
// shmat：生成共享内存
// shmctl：设置共享内存属性

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

#define SEMFILEPATH "./05_Sem.txt"
#define SHMSIZE 1024

union semun
{
    int val;                   // value for SETVAL
    struct semid_ds *buf;      // buffer for IPC_STAT & IPC_SET
    unsigned short int *array; // array for GETALL & SETALL
    struct seminfo *__buf;     // buffer for IPC_INFO
};

int Sem_Init_Value(int _SemID)
{
    union semun un;
    un.val = 0;
    if (semctl(_SemID, 1, SETVAL, un) == -1) // 设置1号索引的信号量值
    {
        perror("semctl failed.\n");
        return -1;
    }

    Sem_Get_Value(_SemID);
    return 0;
}

int Sem_Get_Value(int _SemID)
{
    union semun un;
    un.val = 0;

    int nRet = semctl(_SemID, 1, GETVAL, un); // 获取1号索引的信号量值
    if (nRet == -1)
    {
        perror("semctl failed.\n");
        return -1;
    }

    printf("Sem_Get_Value：%ld\n", nRet);

    return 0;
}

int Sem_P(int _SemID)
{
    struct sembuf tsembuf;
    tsembuf.sem_num = 1;
    tsembuf.sem_op = -1;
    // tsembuf.sem_flg = IPC_NOWAIT;
    tsembuf.sem_flg = SEM_UNDO; // 在当前进程结束后，撤销对信号量的更改，防止进程退出未释放信号量，致使其他进程一直阻塞等待

    if (semop(_SemID, &tsembuf, 1) == -1)
    {
        perror("Sem_P failed.\n");
        return -1;
    }

    Sem_Get_Value(_SemID);
    return 0;
}

int Sem_W(int _SemID)
{
    struct sembuf tsembuf;
    tsembuf.sem_num = 1;
    tsembuf.sem_op = 0;
    // tsembuf.sem_flg = IPC_NOWAIT;

    if (semop(_SemID, &tsembuf, 1) == -1)
    {
        perror("Sem_W failed.\n");
        return -1;
    }

    Sem_Get_Value(_SemID);
    return 0;
}

int Sem_V(int _SemID)
{
    struct sembuf tsembuf;
    tsembuf.sem_num = 1;
    tsembuf.sem_op = 1;
    // tsembuf.sem_flg = IPC_NOWAIT;
    tsembuf.sem_flg = SEM_UNDO; // 在当前进程结束后，撤销对信号量的更改，防止进程退出未释放信号量，致使其他进程一直阻塞等待

    if (semop(_SemID, &tsembuf, 1) == -1)
    {
        perror("Sem_V failed.\n");
        return -1;
    }

    Sem_Get_Value(_SemID);
    return 0;
}

int main(int argc, char *argv[], char *envp)
{
    if (argc < 2)
    {
        perror("命令行缺少传入参数\n");
        return -1;
    }

    key_t semKey = ftok(SEMFILEPATH, 1);
    int nSemID = semget(semKey, 4, 0644 | IPC_CREAT);
    printf("nSemID = %ld\n", nSemID);
    if (nSemID == -1)
    {
        perror("semget failed.\n");
        return -1;
    }

    int nShmID = shmget(semKey, SHMSIZE, 0644 | IPC_CREAT);
    void *pvShmStartAdr = shmat(nShmID, NULL, 0);
    if (pvShmStartAdr == (void *)-1)
    {
        perror("shmget failed.\n");
        return -1;
    }

    if (atoi(argv[1]) == 0) // 从共享内存读数据
    {
        char chBuf[SHMSIZE + 1] = {0};

        Sem_Init_Value(nSemID);
        while (1)
        {
            Sem_P(nSemID);

            memset(chBuf, 0, SHMSIZE + 1);
            memcpy(chBuf, pvShmStartAdr, SHMSIZE);
            printf("Read：%s\n", chBuf);
        }
    }
    else if (atoi(argv[1]) == 1) // 向共享内存写数据
    {
        int nFreq = 0;
        while (1)
        {
            memset(pvShmStartAdr, 0, SHMSIZE);
            sprintf(pvShmStartAdr, "%ld", nFreq++);

            Sem_V(nSemID);
            sleep(1);
        }
    }
    else if (atoi(argv[1]) == 2) // 删除信号量集、共享内存
    {
        shmctl(nShmID, IPC_RMID, NULL);
        union semun un;
        if (nSemID != -1)
            semctl(nSemID, 1, IPC_RMID, un);
    }

    return 0;
}