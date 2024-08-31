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
#define __USE_GNU   
#include <xlocale.h>
#include <string.h>

#include "HttpRequest.h"
#include "TcpConnection.h"

#define MAX_HTTPHEADER_NUM 32			//http请求头最多可支持的键值对个数

PHTTPREQUEST_INFO HttpRequestInit()
{
	PHTTPREQUEST_INFO ptHttpRequest_Info = (PHTTPREQUEST_INFO)malloc(sizeof(HTTPREQUEST_INFO));
	if (ptHttpRequest_Info == NULL)
		return NULL;

	memset(ptHttpRequest_Info, 0, sizeof(HTTPREQUEST_INFO));

	ptHttpRequest_Info->CurPasreState = PARASEREQLINE;
	ptHttpRequest_Info->HttpHeaderValidNum = 0;
	ptHttpRequest_Info->pHttpHeader_Info = (PHTTPHEADER_INFO)calloc(sizeof(HTTPHEADER_INFO), MAX_HTTPHEADER_NUM);
	if (ptHttpRequest_Info->pHttpHeader_Info == NULL)
	{
		free(ptHttpRequest_Info);
		ptHttpRequest_Info = NULL;
		return NULL;
	}

	ptHttpRequest_Info->Type = NULL;
	ptHttpRequest_Info->url = NULL;
	ptHttpRequest_Info->Version = NULL;

	return ptHttpRequest_Info;
}

int HttpRequestReset(PHTTPREQUEST_INFO _pHttpRequest_Info)
{
	if (_pHttpRequest_Info == NULL)
		return -1;

	_pHttpRequest_Info->CurPasreState = PARASEREQLINE;

	for (int i = 0; i < MAX_HTTPHEADER_NUM; i++)
	{
		free(_pHttpRequest_Info->pHttpHeader_Info[i].Key);
		free(_pHttpRequest_Info->pHttpHeader_Info[i].Value);
	}
	memset(_pHttpRequest_Info->pHttpHeader_Info, 0, MAX_HTTPHEADER_NUM);

	_pHttpRequest_Info->HttpHeaderValidNum = 0;
	if (_pHttpRequest_Info->Type != NULL)
	{
		free(_pHttpRequest_Info->Type);
		_pHttpRequest_Info->Type = NULL;
	}

	if (_pHttpRequest_Info->url != NULL)
	{
		free(_pHttpRequest_Info->url);
		_pHttpRequest_Info->url = NULL;
	}

	if (_pHttpRequest_Info->Version != NULL)
	{
		free(_pHttpRequest_Info->Version);
		_pHttpRequest_Info->Version = NULL;
	}

	return 0;
}

int HttpRequestDestory(PHTTPREQUEST_INFO _pHttpRequest_Info)
{
	if (_pHttpRequest_Info == NULL)
		return -1;

	HttpRequestReset(_pHttpRequest_Info);

	if (_pHttpRequest_Info->pHttpHeader_Info != NULL)
	{
		free(_pHttpRequest_Info->pHttpHeader_Info);
		_pHttpRequest_Info->pHttpHeader_Info = NULL;
	}

	free(_pHttpRequest_Info);
	_pHttpRequest_Info = NULL;

	return 0;
}

int HttpRequestParase(PHTTPREQUEST_INFO _pHttpRequest_Info, PBUFFER_INFO _pBuffer_Info,
	PHTTPRESPONSE_INFO _pHttpResponse_Info, PBUFFER_INFO _pSendBuf, int _SocketFd)
{
	while (_pHttpRequest_Info->CurPasreState != PARASEREQDONE)
	{
		switch (_pHttpRequest_Info->CurPasreState)
		{
		case PARASEREQLINE:			//解析请求行数据
			if (HttpRequestParaseLine(_pHttpRequest_Info, _pBuffer_Info) != 0)
				return -1;
			break;
		case PARASEREQHEADERS:		//解析请求头数据
			if (HttpRequestParaseHeader(_pHttpRequest_Info, _pBuffer_Info) == -1)
				return -1;
			break;
		case PARASEREQBODY:
			//TODO:暂时没有实现post请求，如果有post请求则需要对其数据体进行解析
			_pHttpRequest_Info->CurPasreState = PARASEREQDONE;
			break;
		case PARASEREQDONE:
			break;
		default:
			break;
		}

		// 响应客户端
		if (_pHttpRequest_Info->CurPasreState == PARASEREQDONE)
		{
			//根据http的请求，准备http响应数据
			HttpRequestProcess(_pHttpRequest_Info, _pHttpResponse_Info);

			//发送http状态行、响应头、空行、数据体
			HttpResponsePrepareMsg(_pHttpResponse_Info, _pSendBuf, _SocketFd);
		}
	}

	_pHttpRequest_Info->CurPasreState = PARASEREQLINE;
	return 0;
}

enum HTTPREQUEST_STATE HttpRequestGetState(PHTTPREQUEST_INFO _pHttpRequest_Info)
{
	return _pHttpRequest_Info->CurPasreState;
}

int HttpRequestAddHeader(PHTTPREQUEST_INFO _pHttpRequest_Info, const char* _Key, const char* _Value)
{
	int nKeyLength = strlen(_Key);
	int nValueLength = strlen(_Value);

	_pHttpRequest_Info->pHttpHeader_Info[_pHttpRequest_Info->HttpHeaderValidNum].Key = (char*)malloc(nKeyLength);
	_pHttpRequest_Info->pHttpHeader_Info[_pHttpRequest_Info->HttpHeaderValidNum].Value = (char*)malloc(nValueLength);

	if (_pHttpRequest_Info->pHttpHeader_Info[_pHttpRequest_Info->HttpHeaderValidNum].Key == NULL)
		return -1;

	if (_pHttpRequest_Info->pHttpHeader_Info[_pHttpRequest_Info->HttpHeaderValidNum].Value == NULL)
	{
		free(_pHttpRequest_Info->pHttpHeader_Info[_pHttpRequest_Info->HttpHeaderValidNum].Key);
		_pHttpRequest_Info->pHttpHeader_Info[_pHttpRequest_Info->HttpHeaderValidNum].Key = NULL;
		return -1;
	}

	memcpy(_pHttpRequest_Info->pHttpHeader_Info[_pHttpRequest_Info->HttpHeaderValidNum].Key, _Key, nKeyLength);
	memcpy(_pHttpRequest_Info->pHttpHeader_Info[_pHttpRequest_Info->HttpHeaderValidNum].Value, _Value, nValueLength);

	return 0;
}

char* HttpRequestQueryHeader(PHTTPREQUEST_INFO _pHttpRequest_Info, const char* _Key)
{
	if (_pHttpRequest_Info == NULL || _Key[0] == '\0')
		return NULL;

	for (int i = 0; i < _pHttpRequest_Info->HttpHeaderValidNum; i++)
	{
		if (strncasecmp(_pHttpRequest_Info->pHttpHeader_Info[i].Key, _Key, strlen(_Key)) == 0)
			return _pHttpRequest_Info->pHttpHeader_Info[i].Value;
	}

	return NULL;
}

//切分请求行数据
static char* SplitRequestLineData(const char* _pStartPos, const char* _pEndPos, const char* _pSerchData, char** _ppData)
{
	int nLength = _pEndPos - _pStartPos;																//有效长度

	if (_pSerchData != NULL)
		nLength = (char*)memmem(_pStartPos, _pEndPos - _pStartPos, _pSerchData, strlen(_pSerchData)) - _pStartPos;

	char* pChTmp = (char*)calloc(nLength + 1, 1);
	if (pChTmp == NULL)
		return NULL;
	strncpy(pChTmp, _pStartPos, nLength);

	*_ppData = pChTmp;

	return _pStartPos + nLength + 1;
}

int HttpRequestParaseLine(PHTTPREQUEST_INFO _pHttpRequest_Info, PBUFFER_INFO _pBuffer_Info)
{
	//使用指针进行请求行解析操作，可兼容各种长度的请求数据要求

	char* pchEndPos = BufferGetCRLFNearestPtr(_pBuffer_Info);											//换行符起始地址
	if (pchEndPos == NULL)
		return -1;

	char* pchStartPos = _pBuffer_Info->pStartPtr + _pBuffer_Info->ReadPos;								//起始地址
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
	pchStartPos = SplitRequestLineData(pchStartPos, pchEndPos, " ", &_pHttpRequest_Info->Type);
	pchStartPos = SplitRequestLineData(pchStartPos, pchEndPos, " ", &_pHttpRequest_Info->url);
	SplitRequestLineData(pchStartPos, pchEndPos, NULL, &_pHttpRequest_Info->Version);

#endif
	//为之后解析请求头数据做准备
	_pBuffer_Info->ReadPos += (nHttpLineLength + 2);
	_pHttpRequest_Info->CurPasreState = PARASEREQHEADERS;

	return 0;
}

int HttpRequestParaseHeader(PHTTPREQUEST_INFO _pHttpRequest_Info, PBUFFER_INFO _pBuffer_Info)
{
	//使用指针进行请求头解析操作，可兼容各种长度的请求数据要求

	char* pchEndPos = BufferGetCRLFNearestPtr(_pBuffer_Info);											//换行符起始地址
	if (pchEndPos == NULL)
		return -1;

	char* pchStartPos = _pBuffer_Info->pStartPtr + _pBuffer_Info->ReadPos;								//起始地址
	int nHttpHeaderLength = pchEndPos - pchStartPos;													//请求头数据块大小

	char* pchTmp = memmem(pchStartPos, nHttpHeaderLength, ": ", 2);
	int nKeyLength = pchTmp - pchStartPos;																//key长度
	if (pchTmp != NULL && nKeyLength != 0)
	{
		char* pchKey = calloc(nKeyLength + 1, 1);
		if (pchKey == NULL)
		{
			perror("calloc failed");
			return -1;
		}

		strncpy(pchKey, pchStartPos, nKeyLength);

		char* pchValue = calloc(pchEndPos - (pchTmp + 2) + 1, 1);
		if (pchValue == NULL)
		{
			free(pchKey);
			perror("calloc failed");
			return -1;
		}

		strncpy(pchValue, pchTmp + 2, pchEndPos - (pchTmp + 2));

		_pHttpRequest_Info->pHttpHeader_Info[_pHttpRequest_Info->HttpHeaderValidNum].Key = pchKey;
		_pHttpRequest_Info->pHttpHeader_Info[_pHttpRequest_Info->HttpHeaderValidNum].Value = pchValue;
		_pHttpRequest_Info->HttpHeaderValidNum++;

		_pBuffer_Info->ReadPos += nHttpHeaderLength + 2;
	}
	else //解析到\r\n空行数据
	{
		_pBuffer_Info->ReadPos += 2;

		//TODO:后续在此处可以自己扩展解析post请求的数据体
		_pHttpRequest_Info->CurPasreState = PARASEREQBODY;

		return -2;
	}


	return 0;
}


static int HexToDec(char _C)
{
	if (_C >= '0' && _C <= '9')
		return _C - '0';
	else if (_C >= 'a' && _C <= 'f')
		return _C - 'a' + 10;
	else if (_C >= 'A' && _C <= 'F')
		return _C - 'A' + 10;

	return 0;
}

static void DecodeMsg(char* _Des, char* _Src)
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

static
const char* AccordFileType_GetFileMsg(const char* _FileType)
{
	//自右向左查找 '.' 字符，如不存在返回NULL
	const char* pchDot = strrchr(_FileType, '.');

	if (pchDot == NULL)
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

void SendDir(const char* _pDirPath, PBUFFER_INFO _pSendBuf, int _SocketFd)
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

		BufferAppendString(_pSendBuf, chSendBuf);

#ifdef MSG_SEND_AUTO
		BufferSocketSend(_pSendBuf, _SocketFd);
#endif // MSG_SEND_AUTO

		memset(chSendBuf, 0, sizeof chSendBuf);

		free(pchFilePath);
		pchFilePath = NULL;
		free(pptdirent[i]);			//scandir调用时，在内部会申请内存，需释放
		pptdirent[i] = NULL;
	}

	sprintf(chSendBuf + strlen(chSendBuf), "</table></body></html>");
	BufferAppendString(_pSendBuf, chSendBuf);
#ifdef MSG_SEND_AUTO
	BufferSocketSend(_pSendBuf, _SocketFd);
#endif // MSG_SEND_AUTO

	free(pptdirent);				//scandir调用时，在内部会申请内存，需释放
	pptdirent = NULL;
}

void SendFile(const char* _pFilePath, PBUFFER_INFO _pSendBuf, int _SocketFd)
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

int HttpRequestProcess(PHTTPREQUEST_INFO _pHttpRequest_Info, PHTTPRESPONSE_INFO _pHttpResponse_Info)
{
	char* chFilePath = NULL;
	if (strcasecmp(_pHttpRequest_Info->Type, "get"))
	{
		return -1;
	}

	//处理用户请求的静态资源（目录或文件）
	if (strcmp(_pHttpRequest_Info->url, "/") == 0)
	{
		chFilePath = "./";
	}
	else
	{
		//因为在起始函数时，已经将当前目录切换到了客户端访问目录了，所有直接使用相对路径即可
		chFilePath = _pHttpRequest_Info->url + 1;

		char* chFilePathTmp = chFilePath;
		DecodeMsg(chFilePath, chFilePathTmp);
	}

	//获取文件属性
	struct stat tstat;
	if (stat(chFilePath, &tstat) == -1)
	{
		//文件不存在 -- 回复404
		char chTmp[128] = { 0 };

		//状态行添加信息
		_pHttpResponse_Info->StatusCode = NOTFOUND;
		strcpy(_pHttpResponse_Info->StatusMsg, "Not Found");
		strcpy(_pHttpResponse_Info->FileNames, "404.html");

		//响应头
		sprintf(chTmp, "%s\r\n", AccordFileType_GetFileMsg(".html"));
		HttpResponseAddHeader(_pHttpResponse_Info, "content-type", chTmp);

		//TODO:形参不匹配
		_pHttpResponse_Info->SendFuncCallBack = SendFile;
		return 0;
	}

	//判断文件类型
	if (S_ISDIR(tstat.st_mode))
	{
		//将这个目录信息提交到HttpResponse模块

		char chTmp[128] = { 0 };
		//状态行添加信息
		_pHttpResponse_Info->StatusCode = OK;
		strcpy(_pHttpResponse_Info->StatusMsg, "OK");

		if (strlen(chFilePath) >= sizeof _pHttpResponse_Info->FileNames)
		{
			perror("访问文件路径过长");
			exit(0);
		}
		strcpy(_pHttpResponse_Info->FileNames, chFilePath);

		//响应头
		sprintf(chTmp, "%s", AccordFileType_GetFileMsg(".html"));
		HttpResponseAddHeader(_pHttpResponse_Info, "content-type", chTmp);
		HttpResponseAddHeader(_pHttpResponse_Info, "content-length", "-1");

		//TODO:形参不匹配
		_pHttpResponse_Info->SendFuncCallBack = SendDir;
	}
	else
	{
		//将文件的内容发送给客户端

		char chTmp[128] = { 0 };
		//状态行添加信息
		_pHttpResponse_Info->StatusCode = OK;
		strcpy(_pHttpResponse_Info->StatusMsg, "OK");

		if (strlen(chFilePath) >= sizeof _pHttpResponse_Info->FileNames)
		{
			perror("访问文件路径过长");
			exit(0);
		}
		strcpy(_pHttpResponse_Info->FileNames, chFilePath);

		//响应头
		sprintf(chTmp, "%s", AccordFileType_GetFileMsg(chFilePath));
		HttpResponseAddHeader(_pHttpResponse_Info, "content-type", chTmp);

		memset(chTmp, 0, sizeof chTmp);
		sprintf(chTmp, "%ld", tstat.st_size);
		HttpResponseAddHeader(_pHttpResponse_Info, "content-length", chTmp);

		//TODO:形参不匹配
		_pHttpResponse_Info->SendFuncCallBack = SendFile;
	}

	return 0;
}
