/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.09
描  述: 三种IO交互方式应用层测试
备  注:
修改记录:

  1.  日期: 2025.01.09
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>            //Windows.h和SetupAPI.h引用不能交换顺序，否则会导致编译报错
#include <SetupAPI.h>
#include <initguid.h>
#include <locale.h>

#pragma comment(lib, "SetupAPI.lib")

using namespace std;

#define RTN_FAILURE                 -2                //函数执行失败            
#define RTN_INPARAMERROR            -1                //传入参数错误
#define RTN_SUCCESS                  0                //传入执行成功

#define DEVINTERFACE_MAX_NUM        16                //设备接口名称最大数量
#define DEVINTERFACE_NAME_MAX_LEN   2048              //设备接口名称最大长度

//Function 需要从 0x800 开始，前面的被内核系统占用
#define IO_NUMCONVER_CODE	        CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)			//数字转换
#define IO_READ_REGEDIT_NUM_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)			//读取注册表数字
#define IO_READ_REGEDIT_BOOLE_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_NEITHER, FILE_ANY_ACCESS)			//读取注册表布尔
#define IO_READ_REGEDIT_STRING_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)		//读取注册表字符串

DEFINE_GUID(INTERFACEGUID,
    0xA33317FD, 0xA262, 0x4E2E, 0xAB, 0x0F, 0x22, 0x8D, 0xC7, 0xDF, 0xF4, 0xAB);

/// <summary>
/// 设备接口相关信息
/// </summary>
typedef struct _DEVICEINTERFACE_INFO
{
    WCHAR DevInterfaceName[DEVINTERFACE_MAX_NUM][DEVINTERFACE_NAME_MAX_LEN];    //设备接口文件名称
    UCHAR DevInterfaceNum;                                                      //设备接口文件数量
}DEVICEINTERFACE_INFO, * PDEVICEINTERFACE_INFO;

/// <summary>
/// 获取当前所有设备接口信息
/// </summary>
/// <param name="_pDevInterface_Info"></param>
/// <returns></returns>
INT32 GetCurDevInterface(PDEVICEINTERFACE_INFO _pDevInterface_Info)
{
    if (!_pDevInterface_Info)
        return RTN_INPARAMERROR;

    HDEVINFO tHDevInfo = { 0 };
    SP_DEVICE_INTERFACE_DATA tSPDevData = { 0 };
    PSP_DEVICE_INTERFACE_DETAIL_DATA_W ptSPDevDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)malloc(DEVINTERFACE_NAME_MAX_LEN);
    if (!ptSPDevDetailData)
    {
        cerr << "PSP_DEVICE_INTERFACE_DETAIL_DATA_W malloc is err." << endl;
        return RTN_FAILURE;
    }

    //获取设备信息集
    tHDevInfo = SetupDiGetClassDevs(&INTERFACEGUID, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
    if (tHDevInfo == INVALID_HANDLE_VALUE)
    {
        cerr << "SetupDiGetClassDevs is err." << endl;
        return RTN_FAILURE;
    }

    tSPDevData.cbSize = sizeof(tSPDevData);

    RtlZeroMemory(_pDevInterface_Info, sizeof(*_pDevInterface_Info));

    for (size_t i = 0; i < DEVINTERFACE_MAX_NUM; i++)               //最多支持DEVINTERFACE_MAX_NUM个同种硬件设备
    {
        if (!SetupDiEnumDeviceInterfaces(tHDevInfo, NULL, &INTERFACEGUID, i, &tSPDevData))      //枚举包含在设备信息集中的设备接口
        {
            break;
        }

        RtlZeroMemory(ptSPDevDetailData, DEVINTERFACE_NAME_MAX_LEN);
        ptSPDevDetailData->cbSize = sizeof(*ptSPDevDetailData);
        if (SetupDiGetDeviceInterfaceDetail(tHDevInfo, &tSPDevData, ptSPDevDetailData, DEVINTERFACE_NAME_MAX_LEN, NULL, NULL))   //获取设备接口名称的详细信息  
        {
            printf("%ls\n", ptSPDevDetailData->DevicePath);
            wcscpy(_pDevInterface_Info->DevInterfaceName[_pDevInterface_Info->DevInterfaceNum], ptSPDevDetailData->DevicePath);
            _pDevInterface_Info->DevInterfaceNum++;
        }
    }

    free(ptSPDevDetailData);
    ptSPDevDetailData = NULL;

    return RTN_SUCCESS;
}

int main()
{
    setlocale(LC_ALL, "");

    DEVICEINTERFACE_INFO tDevInterface_Info = { 0 };

    if (GetCurDevInterface(&tDevInterface_Info) != RTN_SUCCESS && tDevInterface_Info.DevInterfaceNum > 0)
    {
        cerr << "GetCurDevInterface is err." << endl;
        return RTN_SUCCESS;
    }

    DWORD dwRet = 0;
    HANDLE hDevice = CreateFile(tDevInterface_Info.DevInterfaceName[0],
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

    DWORD dwOutNum = 0;
    WCHAR wchStrContent[128] = { 0 };

    if (!DeviceIoControl(hDevice, IO_READ_REGEDIT_NUM_CODE, NULL, 0, &dwOutNum, sizeof dwOutNum, &dwRet, NULL))
    {
        cout << "DeviceIoControl is err." << GetLastError() << endl;
        CloseHandle(hDevice);
        return EXIT_FAILURE;
    }

    printf("读取到的数字: %d\n", dwOutNum);

    if (!DeviceIoControl(hDevice, IO_READ_REGEDIT_STRING_CODE, NULL, 0, wchStrContent, sizeof(wchStrContent), &dwRet, NULL))
    {
        cout << "DeviceIoControl is err." << GetLastError() << endl;
        CloseHandle(hDevice);
        return EXIT_FAILURE;
    }

    printf("读取到的字符串: %ls\n", wchStrContent);

    CloseHandle(hDevice);

    return RTN_SUCCESS;
}

