/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	DriverLoader.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.12
��  ��: ʵ��һ��windows �������Զ�������
��  ע:
�޸ļ�¼:

  1.  ����: 2024.11.12
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	SC_HANDLE hScManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);		//����һ��SC�������
	if (hScManager == NULL)
	{
		cout << "�����������ʧ��" << endl;
		return EXIT_FAILURE;
	}

	SC_HANDLE hService = CreateService(hScManager, TEXT("mydriver"), TEXT("mydriver"),
		SERVER_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE,
		TEXT("./02_02_FirstDiverDemo.sys"), NULL, NULL, NULL, NULL, NULL);	//����һ������
	if (hService == NULL)
	{
		if (GetLastError() == ERROR_SERVICE_EXISTS)
		{
			hService = OpenService(hScManager, TEXT("mydriver"), SERVER_ALL_ACCESS);
			if (hService == NULL)
			{
				cout << "�򿪷���ʧ��" << endl;
				CloseServiceHandle(hScManager);
				return EXIT_FAILURE;
			}
		}
		else
		{
			cout << "��������ʧ��" << endl;
			CloseServiceHandle(hScManager);
			return EXIT_FAILURE;
		}
	}

	if (!StartService(hService, NULL, NULL))										//��������
	{
		cout << "��������ʧ��: err = " << GetLastError() << endl;
		CloseServiceHandle(hService);
		CloseServiceHandle(hScManager);
		return EXIT_FAILURE;
	}

	getchar();

	SERVICE_STATUS tStatus;

	ControlService(hService, SERVICE_CONTROL_STOP, &tStatus);				//ֹͣ����
	DeleteService(hService);												//ɾ������

	CloseServiceHandle(hService);
	CloseServiceHandle(hScManager);

	return EXIT_SUCCESS;
}

