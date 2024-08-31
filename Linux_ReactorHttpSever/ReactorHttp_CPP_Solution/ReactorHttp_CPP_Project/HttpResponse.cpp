//�ļ�������
//      ʵ��һ����Ӧhttp����ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/30
//�޸ļ�¼��
//      2024/1/30     �½�
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
	//״̬��
	sprintf(chTmp, "http/1.1 %d %s\r\n", (int)this->StatusCode, this->m_mapStatusMsg.at(this->StatusCode).data());
	_pSendBuf->AppendString(chTmp);
	_pSendBuf->SocketSend(_SocketFd);

	//��Ӧͷ
	for (auto item : this->m_mapHttpHeaders)
	{
		sprintf(chTmp, "%s: %s\r\n", item.first.data(), item.second.data());
		_pSendBuf->AppendString(chTmp);
		_pSendBuf->SocketSend(_SocketFd);
	}

	//����
	_pSendBuf->AppendString("\r\n");
	_pSendBuf->SocketSend(_SocketFd);

	//�ظ�������
	this->m_pSendFuncCallBack(this->m_strFileNames.data(), _pSendBuf, _SocketFd);
	return 0;
}
