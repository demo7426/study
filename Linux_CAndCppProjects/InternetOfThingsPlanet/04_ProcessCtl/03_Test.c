#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    int i = 0;
    while (argv[i])
    {
        printf("%s\n", argv[i++]);
    }

    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i++]);
    }
    
    return 0;
}