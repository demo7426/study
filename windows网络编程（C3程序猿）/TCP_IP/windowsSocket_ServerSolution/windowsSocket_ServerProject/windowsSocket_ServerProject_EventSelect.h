#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include<WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

/// <summary>
/// ͨ�ŷ�����¼�ѡ��ģ��
/// </summary>
/// <returns></returns>
int Test_EventSelect();

/// <summary>
/// ͨ�ŷ�����¼�ѡ��ģ�ͣ������Ż���̬����������
/// �������в�ѯsocket
/// </summary>
/// <returns></returns>
int Test_EventSelect_OptimizedCode();