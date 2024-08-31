//文件描述：
//      实现一个响应http请求模块
//作者：钱锐
//时间：2024/1/30
//修改记录：
//      2024/1/30     新建
#pragma once
#include "Buffer.h"

enum HTTPRESPONSE_STATUSCODE
{
	UNKNOWN,
	OK = 200,					//接收成功
	MOVEDPERMANENTLY = 301,		//永久重定向
	MOVEDTEMPORARILY = 302,		//暂时重定向
	BADREQUEST = 400,			//错误的请求
	NOTFOUND = 404				//没有找到对应的文件路径
};

// 键值对
struct _HTTPRESQPOSE_HEADER_INFO
{
	//TODO:http协议内部请求头信息的键值对信息有越界风险，后期可以对数组扩容
	char Key[32];				//键
	char Value[128];			//值
};

typedef void (*HttpResponseFunc)(const char* _pFileName, PBUFFER_INFO _pSendBuf, int _SocketFd);

typedef struct _HTTPRESPONSE_INFO
{
	//状态行：状态码、状态信息
	enum HTTPRESPONSE_STATUSCODE StatusCode;				//状态码
	char StatusMsg[128];									//状态信息

	//响应头
	struct _HTTPRESQPOSE_HEADER_INFO* pHttpHeaders;			//响应头键值对信息
	int HeadersValidNum;									//响应头键值对有效数量

	char FileNames[2048];									//文件路径
	HttpResponseFunc SendFuncCallBack;						//发送http响应数据回调函数
}HTTPRESPONSE_INFO, *PHTTPRESPONSE_INFO;

//初始化
PHTTPRESPONSE_INFO HttpResponseInit();

//销毁
int HttpResponseDestroy(PHTTPRESPONSE_INFO _pHttpResponse_Info);

//添加键值对
int HttpResponseAddHeader(PHTTPRESPONSE_INFO _pHttpResponse_Info, const char* _pKey, const char* _pValue);

//将http的请求行、请求头写入到发送缓冲区 _pSendBuf
int HttpResponsePrepareMsg(PHTTPRESPONSE_INFO _pHttpResponse_Info, PBUFFER_INFO _pSendBuf, int _SocketFd);
