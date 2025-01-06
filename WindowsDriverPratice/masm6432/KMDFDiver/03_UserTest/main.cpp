/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.06
描  述: wdf用户态访问WDF驱动程序
备  注:
修改记录:

  1.  日期: 2025.01.06
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/

#include <Windows.h>
#include <iostream>

using namespace std;

int main(void)
{
    HANDLE hDevice = CreateFile(TEXT("\\\\.\\HelloWDF"),
        GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        cout << "CreateFile is err." << endl;
        return EXIT_FAILURE;
    }

    CloseHandle(hDevice);

    return EXIT_SUCCESS;
}




