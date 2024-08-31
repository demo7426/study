// 设置、获取Linux进程环境变量
//一共有一个全局变量、三个API函数，分别为setenv、getenv、unsetenv

// 通过全局变量environ获取所有的进程环境变量
// setenv 设置或修改指定的环境变量 getenv 获取指定的环境变量的值 unsetenv 删除指定的环境变量

#include <stdio.h>
#include <stdlib.h>

// 打印所有环境变量
void Test_01(void)
{
    extern char **environ;

    int i = 0;
    while (environ[i])
    {
        printf("%s\n", environ[i++]);
    }
}

int Printf_CurEnv(const char* _EnvName)
{
    if (_EnvName == NULL)
        return -1;
    printf("Env：%s = %s\n", _EnvName, getenv(_EnvName));
    return 1;
}

void Test_02(void)
{
    const char* chEnvName = "TEST";
    if (setenv(chEnvName, "123456789", 0) != 0)
        perror("Setenv error.");

    Printf_CurEnv(chEnvName);
    unsetenv(chEnvName);
    Printf_CurEnv(chEnvName);
}

int main(int argc, char *argv[])
{
    Test_02();
    return 0;
}
