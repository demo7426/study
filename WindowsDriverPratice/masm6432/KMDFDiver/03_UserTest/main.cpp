/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.cpp
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.06
��  ��: wdf�û�̬����WDF��������
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.06
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

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




