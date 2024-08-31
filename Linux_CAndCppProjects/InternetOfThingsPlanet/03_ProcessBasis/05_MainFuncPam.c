// main函数输入参数
// 命令行参数、环境变量信息为先存储命令行参数，后存储环境变量，中间用NULL(占4位大小)隔开

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //测试命令行参数和环境变量是否为连续存储
    printf("0x%x, 0x%x\n", &(argv[argc -1]), envp);

    int i = 0;
    for (i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
    
    while (envp[i])
    {
        printf("%s\n", envp[i++]);
    }
    
    return 0;
}
