#include<stdio.h>

extern int Func01();
extern int Func02();

int main()
{
    int nFrequency = 0;
    while (1)
    {
        if (nFrequency % 200 == 0)
        {
            nFrequency = 0;
        }
        nFrequency++;
    }
    

    int* pValue = NULL;
    *pValue = 11;
    int nValue[2] = {10, 20};
    nValue[0] = 100;
    Func01();
    Func02();
    return 0;
}