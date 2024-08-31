//文件描述：
//      实现一个解析http请求模块
//作者：钱锐
//时间：2024/1/26
//修改记录：
//      2024/1/26     新建
#pragma once
#include <map>
#include "Buffer.h"
#include "HttpResponse.h"

using namespace std;

enum class HTTPREQUEST_STATE:char
{
	PARASEREQLINE = 0x01,
	PARASEREQHEADERS,
	PARASEREQBODY,
	PARASEREQDONE
};

class CHttpRequest 
{
public:
	CHttpRequest();
	~CHttpRequest();

	// 重置
	int Reset();

	// 解析http所有的请求数据，及内部响应客户端
	int Parase(CBuffer* _pBuffer_Info,
		CHttpResponse* _pHttpResponse_Info, CBuffer* _pSendBuf, int _SocketFd);

	inline void SetType(string _Type)
	{
		m_strType = _Type;
	}
	inline void Seturl(string _url)
	{
		m_strUrl = _url;
	}
	inline void SetVersion(string _Version)
	{
		m_strtVersion = _Version;
	}

private:
	// 获取请求处理状态
	inline auto GetState() -> HTTPREQUEST_STATE const
	{
		return m_eCurPasreState;
	}

	// 添加头键值对数据
	int AddHeader(const string _Key, const string _Value);

	// 根据请求头键得到值
	string QueryHeader(const string _Key);
	// 解析请求行数据，并存入对应位置

	int ParaseLine(CBuffer* _pBuffer_Info);

	// 解析请求头数据，并存入对应位置，每次只能解析一行数据
	int ParaseHeader(CBuffer* _pBuffer_Info);

	// http响应请求
	int Process(CHttpResponse* _pHttpResponse_Info);

	void DecodeMsg(char* _Des, char* _Src);

	const char* AccordFileType_GetFileMsg(const char* _FileType);

	static void SendDir(const char* _pDirPath, CBuffer* _pSendBuf, int _SocketFd);

	static void SendFile(const char* _pFilePath, CBuffer* _pSendBuf, int _SocketFd);

	int HexToDec(char _C);
private:
	string m_strType;									//请求类型
	string m_strUrl;									//用于存储客户端发来的想访问的资源
	string m_strtVersion;								//用于存储客户端发来的http版本号
	map<string, string> m_mapHttpHeader;				//用于存储请求头键值对数据
	HTTPREQUEST_STATE m_eCurPasreState;					//当前解析状态
};


