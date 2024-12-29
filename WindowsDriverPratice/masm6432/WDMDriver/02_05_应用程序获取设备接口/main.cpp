/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.0.1     新建日期: 2024.12.29
描  述: 用户态遍历对应GUID的多个设备接口
备  注:
修改记录:

  1.  日期: 2024.12.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/

#include <iostream>
#include <Windows.h>            //Windows.h和SetupAPI.h引用不能交换顺序，否则会导致编译报错
#include <SetupAPI.h>
#include <initguid.h>

#pragma comment(lib, "SetupAPI.lib")

using namespace std;

DEFINE_GUID(INTERFACEGUID,
    0xA33317FD, 0xA262, 0x4E2E, 0xAB, 0x0F, 0x22, 0x8D, 0xC7, 0xDF, 0xF4, 0xAB);

int main()
{
    constexpr size_t unSysbolicNameMaxLen = 4096;           //符号练级最大长度
    HDEVINFO tHDevInfo;
    SP_DEVICE_INTERFACE_DATA tSPDevData = { 0 };
    PSP_DEVICE_INTERFACE_DETAIL_DATA_W ptSPDevDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)malloc(unSysbolicNameMaxLen);
    if (!ptSPDevDetailData)
    {
        cerr << "PSP_DEVICE_INTERFACE_DETAIL_DATA_W malloc is err." << endl;
        return EXIT_FAILURE;
    }
    
    //获取设备信息集
    tHDevInfo = SetupDiGetClassDevs(&INTERFACEGUID, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
    if (tHDevInfo == INVALID_HANDLE_VALUE)
    {
        cerr << "SetupDiGetClassDevs is err." << endl;
        return EXIT_FAILURE;
    }

    tSPDevData.cbSize = sizeof(tSPDevData);

    for (size_t i = 0; i < 2048; i++)               //最多支持2048个同种硬件设备
    {
        if (!SetupDiEnumDeviceInterfaces(tHDevInfo, NULL, &INTERFACEGUID, i, //i为驱动文件索引
            &tSPDevData))       //枚举包含在设备信息集中的设备接口
        {
            break;
        }

        RtlZeroMemory(ptSPDevDetailData, unSysbolicNameMaxLen);
        ptSPDevDetailData->cbSize = sizeof(*ptSPDevDetailData);
        if (SetupDiGetDeviceInterfaceDetail(tHDevInfo, &tSPDevData, ptSPDevDetailData, unSysbolicNameMaxLen, NULL, NULL))   //获取设备接口名称的详细信息
        {
            printf("%ls\n", ptSPDevDetailData->DevicePath);
        }
    }

    free(ptSPDevDetailData);
    ptSPDevDetailData = NULL;

    return EXIT_SUCCESS;
}


