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

CHttpResponse::CHttpResponse()
{
	this->m_strFileNames.clear();
	this->m_mapHttpHeaders.clear();
	this->StatusCode = HTTPRESPONSE_STATUSCODE::UNKNOWN;
	this->m_pSendFuncCallBack = nullptr;
}

int CHttpResponse::AddHeader(const string _pKey, const string _pValue)
{
	if (_pKey.empty() || _pValue.empty())
		return -1;

	this->m_mapHttpHeaders.emplace(_pKey, _pValue);
	return 0;
}

int CHttpResponse::PrepareMsg(CBuffer* _pSendBuf, int _SocketFd)
{
	char chTmp[1024] = { 0 };
	//状态行
	sprintf(chTmp, "http/1.1 %d %s\r\n", (int)this->StatusCode, this->m_mapStatusMsg.at(this->StatusCode).data());
	_pSendBuf->AppendString(chTmp);
	_pSendBuf->SocketSend(_SocketFd);

	//响应头
	for (auto item : this->m_mapHttpHeaders)
	{
		sprintf(chTmp, "%s: %s\r\n", item.first.data(), item.second.data());
		_pSendBuf->AppendString(chTmp);
		_pSendBuf->SocketSend(_SocketFd);
	}

	//空行
	_pSendBuf->AppendString("\r\n");
	_pSendBuf->SocketSend(_SocketFd);

	//回复的数据
	this->m_pSendFuncCallBack(this->m_strFileNames.data(), _pSendBuf, _SocketFd);
	return 0;
}
