//�ļ�������
//      ʵ��һ����Ӧhttp����ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/22
//�޸ļ�¼��
//      2024/2/22     �½�
#pragma once
#include <map>
#include <functional>
#include "Buffer.h"

using namespace std;

enum HTTPRESPONSE_STATUSCODE
{
	UNKNOWN,
	OK = 200,					//���ճɹ�
	MOVEDPERMANENTLY = 301,		//�����ض���
	MOVEDTEMPORARILY = 302,		//��ʱ�ض���
	BADREQUEST = 400,			//���������
	NOTFOUND = 404				//û���ҵ���Ӧ���ļ�·��
};

class CHttpResponse
{
	//typedef void (*HttpResponseFunc)(const char* _pFileName, CBuffer* _pSendBuf, int _SocketFd);
	using HttpResponseFunc = function<void(const char* _pFileName, CBuffer* _pSendBuf, int _SocketFd)>;
public:
	CHttpResponse();
	~CHttpResponse() {};

	//��Ӽ�ֵ��
	int AddHeader(const string _pKey, const string _pValue);

	//��http�������С�����ͷд�뵽���ͻ����� _pSendBuf
	int PrepareMsg(CBuffer* _pSendBuf, int _SocketFd);

	inline void SetStatusCode(HTTPRESPONSE_STATUSCODE _StatusCode)
	{
		this->StatusCode = _StatusCode;
	}

	inline void SetFileName(string _FileName)
	{
		this->m_strFileNames = _FileName;
	}
	inline void SetSendFuncCallBack(HttpResponseFunc _SendFuncCallBack)
	{
		this->m_pSendFuncCallBack = _SendFuncCallBack;
	}

private:
	//״̬�У�״̬�롢״̬��Ϣ
	enum HTTPRESPONSE_STATUSCODE StatusCode;				//״̬��

	//״̬��Ϣ
	const map<HTTPRESPONSE_STATUSCODE, string> m_mapStatusMsg =
	{
		{HTTPRESPONSE_STATUSCODE::OK, "OK"},
		{HTTPRESPONSE_STATUSCODE::MOVEDPERMANENTLY, "MOVEDPERMANENTLY"},
		{HTTPRESPONSE_STATUSCODE::MOVEDTEMPORARILY, "MOVEDTEMPORARILY"},
		{HTTPRESPONSE_STATUSCODE::BADREQUEST, "BADREQUEST"},
		{HTTPRESPONSE_STATUSCODE::NOTFOUND, "NOTFOUND"}
	};

	//��Ӧͷ
	map<string, string> m_mapHttpHeaders;						//��Ӧͷ��ֵ����Ϣ

	string m_strFileNames;										//�ļ�·��
	HttpResponseFunc m_pSendFuncCallBack;						//����http��Ӧ���ݻص�����
};
