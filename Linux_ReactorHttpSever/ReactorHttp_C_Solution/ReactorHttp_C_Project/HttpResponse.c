//文件描述：
//      实现一个响应http请求模块
//作者：钱锐
//时间：2024/1/30
//修改记录：
//      2024/1/30     新建
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "HttpResponse.h"


#define MAX_HTTPHEADER_NUM 32			//http请求头最多可支持的键值对个数

PHTTPRESPONSE_INFO HttpResponseInit()
{
	PHTTPRESPONSE_INFO pHttpResponse_Info = (PHTTPRESPONSE_INFO)calloc(sizeof(HTTPRESPONSE_INFO), 1);
	if (pHttpResponse_Info == NULL)
		return NULL;

	pHttpResponse_Info->HeadersValidNum = 0;
	pHttpResponse_Info->pHttpHeaders = (struct _HTTPRESQPOSE_HEADER_INFO*)malloc(sizeof(struct _HTTPRESQPOSE_HEADER_INFO) * MAX_HTTPHEADER_NUM);
	if (pHttpResponse_Info->pHttpHeaders == NULL)
	{
		free(pHttpResponse_Info);
		pHttpResponse_Info = NULL;
		return NULL;
	}

	pHttpResponse_Info->SendFuncCallBack = NULL;
	pHttpResponse_Info->StatusCode = UNKNOWN;
	bzero(pHttpResponse_Info->StatusMsg, sizeof pHttpResponse_Info->StatusMsg);
	bzero(pHttpResponse_Info->FileNames, sizeof pHttpResponse_Info->FileNames);

	return pHttpResponse_Info;
}

int HttpResponseDestroy(PHTTPRESPONSE_INFO _pHttpResponse_Info)
{
	if (_pHttpResponse_Info == NULL)
		return -1;

	if (_pHttpResponse_Info->pHttpHeaders == NULL)
	{
		free(_pHttpResponse_Info); 
		_pHttpResponse_Info = NULL;
	}
	else
	{
		free(_pHttpResponse_Info->pHttpHeaders);
		_pHttpResponse_Info->pHttpHeaders = NULL;
		free(_pHttpResponse_Info);
		_pHttpResponse_Info = NULL;
	}
	return 0;
}

int HttpResponseAddHeader(PHTTPRESPONSE_INFO _pHttpResponse_Info, const char* _pKey, const char* _pValue)
{
	if (_pHttpResponse_Info == NULL || _pKey == NULL || _pValue == NULL)
		return -1;

	strncpy(_pHttpResponse_Info->pHttpHeaders[_pHttpResponse_Info->HeadersValidNum].Key, _pKey,
		sizeof(_pHttpResponse_Info->pHttpHeaders[0].Key));
	strncpy(_pHttpResponse_Info->pHttpHeaders[_pHttpResponse_Info->HeadersValidNum].Value, _pValue,
		sizeof(_pHttpResponse_Info->pHttpHeaders[0].Value));

	_pHttpResponse_Info->HeadersValidNum++;
	return 0;
}

int HttpResponsePrepareMsg(PHTTPRESPONSE_INFO _pHttpResponse_Info, PBUFFER_INFO _pSendBuf, int _SocketFd)
{
	char chTmp[1024] = { 0 };
	//状态行
	sprintf(chTmp, "http/1.1 %d %s\r\n", _pHttpResponse_Info->StatusCode, _pHttpResponse_Info->StatusMsg);
	BufferAppendString(_pSendBuf, chTmp);
	BufferSocketSend(_pSendBuf, _SocketFd);

	//响应头
	for (int i = 0; i < _pHttpResponse_Info->HeadersValidNum; i++)
	{
		memset(chTmp, 0, sizeof chTmp);
		sprintf(chTmp, "%s: %s\r\n", _pHttpResponse_Info->pHttpHeaders[i].Key, _pHttpResponse_Info->pHttpHeaders[i].Value);
		BufferAppendString(_pSendBuf, chTmp);
		BufferSocketSend(_pSendBuf, _SocketFd);
	}

	//空行
	BufferAppendString(_pSendBuf, "\r\n");
	BufferSocketSend(_pSendBuf, _SocketFd);

	//回复的数据
	_pHttpResponse_Info->SendFuncCallBack(_pHttpResponse_Info->FileNames, _pSendBuf, _SocketFd);
	return 0;
}
