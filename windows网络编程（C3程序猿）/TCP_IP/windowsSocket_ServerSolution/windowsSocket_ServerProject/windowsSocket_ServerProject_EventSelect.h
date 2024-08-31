#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include<WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

/// <summary>
/// 通信服务端事件选择模型
/// </summary>
/// <returns></returns>
int Test_EventSelect();

/// <summary>
/// 通信服务端事件选择模型（有序优化变态点击的情况）
/// 挨个进行查询socket
/// </summary>
/// <returns></returns>
int Test_EventSelect_OptimizedCode();