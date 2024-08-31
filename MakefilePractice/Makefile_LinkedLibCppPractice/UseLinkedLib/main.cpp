#include"QR_SubClass.h"

int main()
{
    QR_BaseClass *pcBase = new QR_SubClass();
    pcBase->Func01();
    pcBase->Func02();
    pcBase->Func03();

    return 0;
}