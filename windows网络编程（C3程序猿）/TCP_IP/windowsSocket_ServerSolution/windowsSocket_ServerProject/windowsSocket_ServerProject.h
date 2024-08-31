#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include<WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

/// <summary>
/// 通信服务端基础模型
/// </summary>
/// <returns></returns>
int Test_Basic();