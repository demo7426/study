/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.cpp
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2024.12.29
��  ��: �û�̬������ӦGUID�Ķ���豸�ӿ�
��  ע:
�޸ļ�¼:

  1.  ����: 2024.12.29
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#include <iostream>
#include <Windows.h>            //Windows.h��SetupAPI.h���ò��ܽ���˳�򣬷���ᵼ�±��뱨��
#include <SetupAPI.h>
#include <initguid.h>

#pragma comment(lib, "SetupAPI.lib")

using namespace std;

DEFINE_GUID(INTERFACEGUID,
    0xA33317FD, 0xA262, 0x4E2E, 0xAB, 0x0F, 0x22, 0x8D, 0xC7, 0xDF, 0xF4, 0xAB);

int main()
{
    constexpr size_t unSysbolicNameMaxLen = 4096;           //����������󳤶�
    HDEVINFO tHDevInfo;
    SP_DEVICE_INTERFACE_DATA tSPDevData = { 0 };
    PSP_DEVICE_INTERFACE_DETAIL_DATA_W ptSPDevDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)malloc(unSysbolicNameMaxLen);
    if (!ptSPDevDetailData)
    {
        cerr << "PSP_DEVICE_INTERFACE_DETAIL_DATA_W malloc is err." << endl;
        return EXIT_FAILURE;
    }
    
    //��ȡ�豸��Ϣ��
    tHDevInfo = SetupDiGetClassDevs(&INTERFACEGUID, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
    if (tHDevInfo == INVALID_HANDLE_VALUE)
    {
        cerr << "SetupDiGetClassDevs is err." << endl;
        return EXIT_FAILURE;
    }

    tSPDevData.cbSize = sizeof(tSPDevData);

    for (size_t i = 0; i < 2048; i++)               //���֧��2048��ͬ��Ӳ���豸
    {
        if (!SetupDiEnumDeviceInterfaces(tHDevInfo, NULL, &INTERFACEGUID, i, //iΪ�����ļ�����
            &tSPDevData))       //ö�ٰ������豸��Ϣ���е��豸�ӿ�
        {
            break;
        }

        RtlZeroMemory(ptSPDevDetailData, unSysbolicNameMaxLen);
        ptSPDevDetailData->cbSize = sizeof(*ptSPDevDetailData);
        if (SetupDiGetDeviceInterfaceDetail(tHDevInfo, &tSPDevData, ptSPDevDetailData, unSysbolicNameMaxLen, NULL, NULL))   //��ȡ�豸�ӿ����Ƶ���ϸ��Ϣ
        {
            printf("%ls\n", ptSPDevDetailData->DevicePath);
        }
    }

    free(ptSPDevDetailData);
    ptSPDevDetailData = NULL;

    return EXIT_SUCCESS;
}


