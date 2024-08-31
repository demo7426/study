//文件描述：
//      实现一个响应http请求模块
//作者：钱锐
//时间：2024/2/22
//修改记录：
//      2024/2/22     新建
#pragma once
#include <map>
#include <functional>
#include "Buffer.h"

using namespace std;

enum HTTPRESPONSE_STATUSCODE
{
	UNKNOWN,
	OK = 200,					//接收成功
	MOVEDPERMANENTLY = 301,		//永久重定向
	MOVEDTEMPORARILY = 302,		//暂时重定向
	BADREQUEST = 400,			//错误的请求
	NOTFOUND = 404				//没有找到对应的文件路径
};

class CHttpResponse
{
	//typedef void (*HttpResponseFunc)(const char* _pFileName, CBuffer* _pSendBuf, int _SocketFd);
	using HttpResponseFunc = function<void(const char* _pFileName, CBuffer* _pSendBuf, int _SocketFd)>;
public:
	CHttpResponse();
	~CHttpResponse() {};

	//添加键值对
	int AddHeader(const string _pKey, const string _pValue);

	//将http的请求行、请求头写入到发送缓冲区 _pSendBuf
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
	//状态行：状态码、状态信息
	enum HTTPRESPONSE_STATUSCODE StatusCode;				//状态码

	//状态信息
	const map<HTTPRESPONSE_STATUSCODE, string> m_mapStatusMsg =
	{
		{HTTPRESPONSE_STATUSCODE::OK, "OK"},
		{HTTPRESPONSE_STATUSCODE::MOVEDPERMANENTLY, "MOVEDPERMANENTLY"},
		{HTTPRESPONSE_STATUSCODE::MOVEDTEMPORARILY, "MOVEDTEMPORARILY"},
		{HTTPRESPONSE_STATUSCODE::BADREQUEST, "BADREQUEST"},
		{HTTPRESPONSE_STATUSCODE::NOTFOUND, "NOTFOUND"}
	};

	//响应头
	map<string, string> m_mapHttpHeaders;						//响应头键值对信息

	string m_strFileNames;										//文件路径
	HttpResponseFunc m_pSendFuncCallBack;						//发送http响应数据回调函数
};
