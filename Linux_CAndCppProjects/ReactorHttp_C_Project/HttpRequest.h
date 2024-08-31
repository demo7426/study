//文件描述：
//      实现一个解析http请求模块
//作者：钱锐
//时间：2024/1/26
//修改记录：
//      2024/1/26     新建
#pragma once
#include "Buffer.h"
#include "HttpResponse.h"

typedef struct _HTTPHEADER_INFO
{
	char* Key;
	char* Value;
}HTTPHEADER_INFO, *PHTTPHEADER_INFO;

enum HTTPREQUEST_STATE
{
	PARASEREQLINE,
	PARASEREQHEADERS,
	PARASEREQBODY,
	PARASEREQDONE
};


typedef struct _HTTPREQUEST_INFO
{
	char* Type;									//请求类型
	char* url;									//用于存储客户端发来的想访问的资源
	char* Version;								//用于存储客户端发来的http版本号
	PHTTPHEADER_INFO pHttpHeader_Info;			//用于存储请求头键值对数据
	int HttpHeaderValidNum;						//请求头的有效键值对个数
	enum HTTPREQUEST_STATE CurPasreState;		//当前解析状态
}HTTPREQUEST_INFO, * PHTTPREQUEST_INFO;

// 初始化
PHTTPREQUEST_INFO HttpRequestInit();

// 重置
int HttpRequestReset(PHTTPREQUEST_INFO _pHttpRequest_Info);

// 销毁对象
int HttpRequestDestory(PHTTPREQUEST_INFO _pHttpRequest_Info);

// 解析http所有的请求数据，及内部响应客户端
int HttpRequestParase(PHTTPREQUEST_INFO _pHttpRequest_Info, PBUFFER_INFO _pBuffer_Info,
	PHTTPRESPONSE_INFO _pHttpResponse_Info, PBUFFER_INFO _pSendBuf, int _SocketFd);

/////////////////////////////////////////内部接口/////////////////////////////////////////

// 获取请求处理状态
enum HTTPREQUEST_STATE HttpRequestGetState(PHTTPREQUEST_INFO _pHttpRequest_Info);

// 添加头键值对数据
int HttpRequestAddHeader(PHTTPREQUEST_INFO _pHttpRequest_Info, const char* _Key, const char* _Value);

// 根据请求头键得到值
char* HttpRequestQueryHeader(PHTTPREQUEST_INFO _pHttpRequest_Info, const char* _Key);

// 解析请求行数据，并存入对应位置
int HttpRequestParaseLine(PHTTPREQUEST_INFO _pHttpRequest_Info, PBUFFER_INFO _pBuffer_Info);

// 解析请求头数据，并存入对应位置，每次只能解析一行数据
int HttpRequestParaseHeader(PHTTPREQUEST_INFO _pHttpRequest_Info, PBUFFER_INFO _pBuffer_Info);

// http响应请求
int HttpRequestProcess(PHTTPREQUEST_INFO _pHttpRequest_Info, PHTTPRESPONSE_INFO _pHttpResponse_Info);
