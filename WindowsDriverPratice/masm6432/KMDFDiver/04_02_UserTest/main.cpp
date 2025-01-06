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

//Function ��Ҫ�� 0x800 ��ʼ��ǰ��ı��ں�ϵͳռ��
#define IO_READ_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)			//������

int main(void)
{
    DWORD dwRet = 0;
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

    if (!DeviceIoControl(hDevice, IO_READ_CODE, NULL, 0, NULL, 0, &dwRet, NULL))
    {
        cout << "DeviceIoControl is err." << endl;
        return EXIT_FAILURE;
    }

    CloseHandle(hDevice);

    return EXIT_SUCCESS;
}




