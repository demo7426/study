//文件描述：
//      实现一个解析http请求模块
//作者：钱锐
//时间：2024/1/26
//修改记录：
//      2024/1/26     新建
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <assert.h>
#include <ctype.h>
//#define __USE_GNU   
//#include <xlocale.h>
#include <string.h>

#include "HttpRequest.h"
#include "TcpConnection.h"

//切分请求行数据
static char* SplitRequestLineData(const char* _pStartPos, const char* _pEndPos, const char* _pSerchData, function<void(string)> _Func)
{
	int nLength = _pEndPos - _pStartPos;																//有效长度

	if (_pSerchData != nullptr)
		nLength = (char*)memmem(_pStartPos, _pEndPos - _pStartPos, _pSerchData, strlen(_pSerchData)) - _pStartPos;

	_Func(string(_pStartPos, nLength));

	return const_cast<char*>(_pStartPos + nLength + 1);
}


int CHttpRequest::HexToDec(char _C)
{
	if (_C >= '0' && _C <= '9')
		return _C - '0';
	else if (_C >= 'a' && _C <= 'f')
		return _C - 'a' + 10;
	else if (_C >= 'A' && _C <= 'F')
		return _C - 'A' + 10;

	return 0;
}

void CHttpRequest::DecodeMsg(char* _Des, char* _Src)
{
	for (; *_Src != '\0'; ++_Src, ++_Des)
	{
		if (_Src[0] == '%' && isxdigit(_Src[1]) && isxdigit(_Src[2]))
		{
			*_Des = HexToDec(_Src[1]) * 16 + HexToDec(_Src[2]);

			_Src += 2;
		}
		else
		{
			*_Des = *_Src;
		}
	}

	*_Des = '\0';
}

const char* CHttpRequest::AccordFileType_GetFileMsg(const char* _FileType)
{
	//自右向左查找 '.' 字符，如不存在返回NULL
	const char* pchDot = strrchr(_FileType, '.');

	if (pchDot == nullptr)
		return "text/plain; charset=utf-8";	//纯文本
	if (strcmp(pchDot, ".html") == 0 || strcmp(pchDot, ".htm") == 0)
		return "text/html; charset=utf-8";
	if (strcmp(pchDot, ".pdf") == 0)
		return "application/pdf";
	if (strcmp(pchDot, ".jpe") == 0)
		return "application/x-jpg";
	if (strcmp(pchDot, ".jpg") == 0)
		return "image/jpeg";
	if (strcmp(pchDot, ".gif") == 0)
		return "image/gif";
	if (strcmp(pchDot, ".png") == 0)
		return "image/png";
	if (strcmp(pchDot, ".css") == 0)
		return "text/css";
	if (strcmp(pchDot, ".au") == 0)
		return "audio/basic";
	if (strcmp(pchDot, ".wav") == 0)
		return "audio/wav";
	if (strcmp(pchDot, ".avi") == 0)
		return "video/x-msvideo";
	if (strcmp(pchDot, ".mov") == 0 || strcmp(pchDot, ".qt") == 0)
		return "video/quicktime";
	if (strcmp(pchDot, ".mpeg") == 0 || strcmp(pchDot, ".mpe") == 0)
		return "video/mpeg";
	if (strcmp(pchDot, ".vrml") == 0 || strcmp(pchDot, ".wrl") == 0)
		return "model/vrml";
	if (strcmp(pchDot, ".midi") == 0 || strcmp(pchDot, ".mid") == 0)
		return "audio/midi";
	if (strcmp(pchDot, ".mp3") == 0)
		return "audio/mpeg";
	if (strcmp(pchDot, ".mp4") == 0)
		return "video/mpeg4";
	if (strcmp(pchDot, ".ogg") == 0)
		return "application/ogg";
	if (strcmp(pchDot, ".pac") == 0)
		return "application/x-ns-proxy-autoconfig";
	if (strcmp(pchDot, ".ico") == 0)
		return "image/x-icon";
	if (strcmp(pchDot, ".docx") == 0)
		return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
	if (strcmp(pchDot, ".doc") == 0)
		return "application/msword";

	return "text/plain; charset=utf-8";
}

//<html>
//    <head>
//        <title>test</title>
//    </head>
//    <body>
//        <table>
//            <tr>
//                <td>列内容</td>
//                <td>列内容</td>
//            </tr>
//            <tr>
//                <td>列内容</td>
//                <td>列内容</td>
//            </tr>
//        </table>
//    </body>
//</html>

void CHttpRequest::SendDir(const char* _pDirPath, CBuffer* _pSendBuf, int _SocketFd)
{
	char* pchFilePath = NULL;										//完整的相对用户访问根目录下的文件路径
	int nFilePathLength = 0;										//完整的相对用户访问根目录下的文件路径长度
	char chSendBuf[4096] = { 0 };
	struct dirent** pptdirent = NULL;
	struct stat tstat;
	int nFileNum = scandir(_pDirPath, &pptdirent, NULL, alphasort);	//获取指定目录下的目录信息

	sprintf(chSendBuf, "<html><head><title>%s</title></head><body><table>", _pDirPath);

	sprintf(chSendBuf + strlen(chSendBuf),
		"<tr><td>%s</td><td>%s</td></tr>", "FileName", "Size");

	for (int i = 0; i < nFileNum; i++)
	{
		nFilePathLength = strlen(pptdirent[i]->d_name) + strlen(_pDirPath) + 2;
		pchFilePath = (char*)malloc(nFilePathLength);
		memset(pchFilePath, 0, nFilePathLength);
		sprintf(pchFilePath, "%s/%s", _pDirPath, pptdirent[i]->d_name);

		stat(pchFilePath, &tstat);

		//判断文件类型
		if (S_ISDIR(tstat.st_mode))
		{
			//拼接目录html信息
			sprintf(chSendBuf + strlen(chSendBuf),
				"<tr><td><a href=\"%s/\">%s</a></td><td>%d</td></tr>", pptdirent[i]->d_name, pptdirent[i]->d_name, tstat.st_size);
		}
		else
		{
			//拼接文件html信息
			sprintf(chSendBuf + strlen(chSendBuf),
				"<tr><td><a href=\"%s\">%s</a></td><td>%d</td></tr>", pptdirent[i]->d_name, pptdirent[i]->d_name, tstat.st_size);
		}

		_pSendBuf->AppendString(chSendBuf);

#ifdef MSG_SEND_AUTO
		_pSendBuf->SocketSend(_SocketFd);
#endif // MSG_SEND_AUTO

		memset(chSendBuf, 0, sizeof chSendBuf);

		free(pchFilePath);
		pchFilePath = NULL;
		free(pptdirent[i]);			//scandir调用时，在内部会申请内存，需释放
		pptdirent[i] = NULL;
	}

	sprintf(chSendBuf + strlen(chSendBuf), "</table></body></html>");
	_pSendBuf->AppendString(chSendBuf);
#ifdef MSG_SEND_AUTO
	_pSendBuf->SocketSend(_SocketFd);
#endif // MSG_SEND_AUTO

	free(pptdirent);				//scandir调用时，在内部会申请内存，需释放
	pptdirent = NULL;
}

void CHttpRequest::SendFile(const char* _pFilePath, CBuffer* _pSendBuf, int _SocketFd)
{
	int nOpenFd = open(_pFilePath, O_RDONLY);
	assert(nOpenFd > 0);							//当文件打开失败的时候，服务器直接抛出异常

#if 0	//send有从用户空间拷贝到内核的操作，与sendfile相比速率较慢（因为当前项目为写入到自己创建的缓冲区，所以只能采取此方式）
	int nReadLength = 0;
	char chReadBuf[4097] = { 0 };
	while (1)
	{
		nReadLength = read(nOpenFd, chReadBuf, sizeof chReadBuf - 1);
		if (nReadLength > 0)
		{
			//send(_ClientFd, chReadBuf, nReadLength, 0);
			CheckBufferWriteSize(_pSendBuf, nReadLength);
			BufferAppendData(_pSendBuf, chReadBuf, nReadLength);

#ifdef MSG_SEND_AUTO
			BufferSocketSend(_pSendBuf, _SocketFd);
#endif // MSG_SEND_AUTO

			//usleep(1);								//给客户端处理数据的时间
		}
		else if (nReadLength == 0)					//文件读取完毕
			break;
		else
			perror("read failed.\n");

		memset(chReadBuf, 0, sizeof chReadBuf);
	}
#else	
	off_t lOffset = 0;
	int nFileSize = lseek(nOpenFd, 0, SEEK_END);
	lseek(nOpenFd, 0, SEEK_SET);

	while (lOffset < nFileSize)
	{
		//sendfile没有从用户空间拷贝到内核的操作
		sendfile(_SocketFd, nOpenFd, &lOffset, nFileSize - lOffset);
	}

#endif

	close(nOpenFd);
}

CHttpRequest::CHttpRequest():m_eCurPasreState(HTTPREQUEST_STATE::PARASEREQLINE)
{
	this->m_strType = this->m_strUrl = this->m_strtVersion = string();
	this->m_mapHttpHeader.clear();
}

CHttpRequest::~CHttpRequest()
{
}

int CHttpRequest::Reset()
{
	this->m_eCurPasreState = HTTPREQUEST_STATE::PARASEREQLINE;
	this->m_strType = this->m_strUrl = this->m_strtVersion = string();
	this->m_mapHttpHeader.clear();
	return 0;
}

int CHttpRequest::Parase(CBuffer* _pBuffer_Info, CHttpResponse* _pHttpResponse_Info, CBuffer* _pSendBuf, int _SocketFd)
{
	while (this->m_eCurPasreState != HTTPREQUEST_STATE::PARASEREQDONE)
	{
		switch (this->m_eCurPasreState)
		{
		case HTTPREQUEST_STATE::PARASEREQLINE:			//解析请求行数据
			if (ParaseLine(_pBuffer_Info) != 0)
				return -1;
			break;
		case HTTPREQUEST_STATE::PARASEREQHEADERS:		//解析请求头数据
			if (ParaseHeader(_pBuffer_Info) == -1)
				return -1;
			break;
		case HTTPREQUEST_STATE::PARASEREQBODY:
			//TODO:暂时没有实现post请求，如果有post请求则需要对其数据体进行解析
			this->m_eCurPasreState = HTTPREQUEST_STATE::PARASEREQDONE;
			break;
		case HTTPREQUEST_STATE::PARASEREQDONE:
			break;
		default:
			break;
		}

		// 响应客户端
		if (this->m_eCurPasreState == HTTPREQUEST_STATE::PARASEREQDONE)
		{
			//根据http的请求，准备http响应数据
			Process(_pHttpResponse_Info);

			//发送http状态行、响应头、空行、数据体
			_pHttpResponse_Info->PrepareMsg(_pSendBuf, _SocketFd);
		}
	}

	this->m_eCurPasreState = HTTPREQUEST_STATE::PARASEREQLINE;
	return 0;
}

int CHttpRequest::AddHeader(const string _Key, const string _Value)
{
	if (_Key == string() || _Value == string())
		return -1;

	this->m_mapHttpHeader.insert(make_pair(_Key, _Value));
	return 0;
}

string CHttpRequest::QueryHeader(const string _Key)
{
	if (_Key == string() || this->m_mapHttpHeader.empty())
		return string();

	auto item = this->m_mapHttpHeader.find(_Key);
	if (item == this->m_mapHttpHeader.end())
		return string();

	return item->second;
}

int CHttpRequest::ParaseLine(CBuffer* _pBuffer_Info)
{
	//使用指针进行请求行解析操作，可兼容各种长度的请求数据要求

	char* pchEndPos = _pBuffer_Info->GetCRLFNearestPtr();												//换行符起始地址
	if (pchEndPos == nullptr)
		return -1;

	char* pchStartPos = _pBuffer_Info->GetStartPtr() + _pBuffer_Info->GetReadPos();						//起始地址
	int nHttpLineLength = pchEndPos - pchStartPos;														//请求行数据块大小

	if (nHttpLineLength <= 0)
		return -1;

#if 0
	//解析请求行请求类型
	int nTypeLength = (char*)memmem(pchStartPos, nHttpLineLength, " ", 1) - pchStartPos;				//请求类型有效长度
	_pHttpRequest_Info->Type = (char*)calloc(nTypeLength + 1, 1);
	if (_pHttpRequest_Info->Type == NULL)
		return -1;
	strncpy(_pHttpRequest_Info->Type, pchStartPos, nTypeLength);

	pchStartPos += nTypeLength;
	pchStartPos += 1;

	//解析请求行请求静态资源
	int nUrlLength = (char*)memmem(pchStartPos, nHttpLineLength - nTypeLength, " ", 1) - pchStartPos;	//请求静态资源有效长度
	_pHttpRequest_Info->url = (char*)calloc(nUrlLength + 1, 1);
	if (_pHttpRequest_Info->url == NULL)
		return -1;
	strncpy(_pHttpRequest_Info->url, pchStartPos, nUrlLength);

	pchStartPos += nUrlLength;
	pchStartPos += 1;

	//解析请求行请求http版本号
	_pHttpRequest_Info->Version = (char*)calloc(pchEndPos - pchStartPos + 1, 1);
	if (_pHttpRequest_Info->Version == NULL)
		return -1;
	strncpy(_pHttpRequest_Info->Version, pchStartPos, pchEndPos - pchStartPos);
#else
	auto objType = bind(&CHttpRequest::SetType, this, placeholders::_1);
	pchStartPos = SplitRequestLineData(pchStartPos, pchEndPos, " ", objType);

	auto objUrl = bind(&CHttpRequest::Seturl, this, placeholders::_1);
	pchStartPos = SplitRequestLineData(pchStartPos, pchEndPos, " ", objUrl);

	auto objVer = bind(&CHttpRequest::SetVersion, this, placeholders::_1);
	SplitRequestLineData(pchStartPos, pchEndPos, nullptr, objVer);

#endif
	//为之后解析请求头数据做准备
	_pBuffer_Info->SetReadPos(_pBuffer_Info->GetReadPos()+ nHttpLineLength + 2);
	this->m_eCurPasreState = HTTPREQUEST_STATE::PARASEREQHEADERS;

	return 0;
}

int CHttpRequest::ParaseHeader(CBuffer* _pBuffer_Info)
{
	//使用指针进行请求头解析操作，可兼容各种长度的请求数据要求

	char* pchEndPos = _pBuffer_Info->GetCRLFNearestPtr();												//换行符起始地址
	if (pchEndPos == nullptr)
		return -1;

	char* pchStartPos = _pBuffer_Info->GetStartPtr() + _pBuffer_Info->GetReadPos();						//起始地址
	int nHttpHeaderLength = pchEndPos - pchStartPos;													//请求头数据块大小

	char* pchTmp = (char*)memmem(pchStartPos, nHttpHeaderLength, ": ", 2);
	int nKeyLength = pchTmp - pchStartPos;																//key长度
	if (pchTmp != NULL && nKeyLength != 0)
	{
		this->m_mapHttpHeader.emplace(string(pchStartPos, nKeyLength), string(pchTmp + 2, pchEndPos - (pchTmp + 2)));

		_pBuffer_Info->SetReadPos(_pBuffer_Info->GetReadPos() + nHttpHeaderLength + 2);
}
	else //解析到\r\n空行数据
	{
		_pBuffer_Info->SetReadPos(_pBuffer_Info->GetReadPos() + 2);

		//TODO:后续在此处可以自己扩展解析post请求的数据体
		this->m_eCurPasreState = HTTPREQUEST_STATE::PARASEREQBODY;

		return -2;
	}


	return 0;
}

int CHttpRequest::Process(CHttpResponse* _pHttpResponse_Info)
{
	const char* chFilePath = nullptr;
	if (strcasecmp(this->m_strType.data(), "get"))
	{
		return -1;
	}

	//处理用户请求的静态资源（目录或文件）
	if (strcmp(this->m_strUrl.data(), "/") == 0)
	{
		chFilePath = "./";
	}
	else
	{
		//因为在起始函数时，已经将当前目录切换到了客户端访问目录了，所有直接使用相对路径即可
		chFilePath = this->m_strUrl.data() + 1;

		const char* chFilePathTmp = chFilePath;
		DecodeMsg(const_cast<char*>(chFilePath), const_cast<char*>(chFilePathTmp));
	}

	//获取文件属性
	struct stat tstat;
	if (stat(chFilePath, &tstat) == -1)
	{
		//文件不存在 -- 回复404
		char chTmp[128] = { 0 };

		//状态行添加信息
		_pHttpResponse_Info->SetStatusCode(HTTPRESPONSE_STATUSCODE::NOTFOUND);
		_pHttpResponse_Info->SetFileName("404.html");

		//响应头
		sprintf(chTmp, "%s\r\n", AccordFileType_GetFileMsg(".html"));
		_pHttpResponse_Info->AddHeader("content-type", chTmp);

		//TODO:形参不匹配
		_pHttpResponse_Info->SetSendFuncCallBack(SendFile);
		return 0;
	}

	//判断文件类型
	if (S_ISDIR(tstat.st_mode))
	{
		//将这个目录信息提交到HttpResponse模块

		char chTmp[128] = { 0 };
		//状态行添加信息
		_pHttpResponse_Info->SetStatusCode(HTTPRESPONSE_STATUSCODE::OK);
		_pHttpResponse_Info->SetFileName(chFilePath);

		//响应头
		sprintf(chTmp, "%s", AccordFileType_GetFileMsg(".html"));
		_pHttpResponse_Info->AddHeader("content-type", chTmp);
		_pHttpResponse_Info->AddHeader("content-length", "-1");

		//TODO:形参不匹配
		_pHttpResponse_Info->SetSendFuncCallBack(SendDir);
	}
	else
	{
		//将文件的内容发送给客户端

		//状态行添加信息
		_pHttpResponse_Info->SetStatusCode(HTTPRESPONSE_STATUSCODE::OK);
		_pHttpResponse_Info->SetFileName(chFilePath);

		//响应头
		_pHttpResponse_Info->AddHeader("content-type", AccordFileType_GetFileMsg(chFilePath));
		_pHttpResponse_Info->AddHeader("content-length", to_string(tstat.st_size));

		//TODO:形参不匹配
		_pHttpResponse_Info->SetSendFuncCallBack(SendFile);
	}

	return 0;
}
