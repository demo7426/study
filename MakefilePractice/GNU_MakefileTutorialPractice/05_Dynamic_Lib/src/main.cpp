
#include <stdio.h>
#include "Add.hpp"
#include "Minus.hpp"

int main(int argc, char *argv[], char *envp[])
{
    int nValue[] = {2, 1};
    printf("%d + %d = %d\n", nValue[0], nValue[1], Add(nValue[0], nValue[1]));
    printf("%d - %d = %d\n", nValue[0], nValue[1], Minus(nValue[0], nValue[1]));
    return 0;
}