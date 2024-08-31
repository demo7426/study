 //启用一个新的进程替换当前子进程；
 //execl、execlp、execle、execv、execvp、execvpe函数均可以启用一个新的进程,只是参数不同
 //（带有p字符函数的会去PATH环境变量下的路径检索是否有可执行程序，可以传入PATH路径下的相对路径）
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define __USE_GNU
#include <unistd.h>

void Test01(void)
{
    int nRtnFork = fork();

    if (nRtnFork == 0)
    {
        int nRtn = -1;
        char* const argv[] = {"123", "456", NULL};
        extern char **environ;

        //启用一个新的进程替换当前子进程
        //nRtn = execl("/home/qianrui/projects/InternetOfThingsPlanet/04_ProcessCtl/03_Test.out", argv[0], argv[1], NULL);//只能传入绝对路径
        //nRtn = execlp("/home/qianrui/projects/InternetOfThingsPlanet/04_ProcessCtl/03_Test.out", argv[0], argv[1], NULL);//可以传入绝对路径或PATH环境变量下的相对路径
        //nRtn = execle("/home/qianrui/projects/InternetOfThingsPlanet/04_ProcessCtl/03_Test.out", argv[0], argv[1], NULL, environ);//只能传入绝对路径
        //nRtn = execv("/home/qianrui/projects/InternetOfThingsPlanet/04_ProcessCtl/03_Test.out", argv);//只能传入绝对路径
        //nRtn = execvp("/home/qianrui/projects/InternetOfThingsPlanet/04_ProcessCtl/03_Test.out", argv);//可以传入绝对路径或PATH环境变量下的相对路径
        nRtn = execvpe("/home/qianrui/projects/InternetOfThingsPlanet/04_ProcessCtl/03_Test.out", argv, environ);//可以传入绝对路径或PATH环境变量下的相对路径

        if (nRtn == -1)
            perror("execl error.\n");

        printf("Children process start.\n");
    }
    else if (nRtnFork > 0)
    {
        printf("Parent process start.\n");
        wait(NULL);//等待子进程结束
    }
    else
        perror("fork error.\n");

}

int main(int argc, char *argv[], char *envp[])
{
    Test01();
    return 0;
}