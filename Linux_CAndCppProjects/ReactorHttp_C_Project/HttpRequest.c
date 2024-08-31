//�ļ�������
//      ʵ��һ������http����ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/26
//�޸ļ�¼��
//      2024/1/26     �½�
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

#define MAX_HTTPHEADER_NUM 32			//http����ͷ����֧�ֵļ�ֵ�Ը���

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
		case PARASEREQLINE:			//��������������
			if (HttpRequestParaseLine(_pHttpRequest_Info, _pBuffer_Info) != 0)
				return -1;
			break;
		case PARASEREQHEADERS:		//��������ͷ����
			if (HttpRequestParaseHeader(_pHttpRequest_Info, _pBuffer_Info) == -1)
				return -1;
			break;
		case PARASEREQBODY:
			//TODO:��ʱû��ʵ��post���������post��������Ҫ������������н���
			_pHttpRequest_Info->CurPasreState = PARASEREQDONE;
			break;
		case PARASEREQDONE:
			break;
		default:
			break;
		}

		// ��Ӧ�ͻ���
		if (_pHttpRequest_Info->CurPasreState == PARASEREQDONE)
		{
			//����http������׼��http��Ӧ����
			HttpRequestProcess(_pHttpRequest_Info, _pHttpResponse_Info);

			//����http״̬�С���Ӧͷ�����С�������
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

//�з�����������
static char* SplitRequestLineData(const char* _pStartPos, const char* _pEndPos, const char* _pSerchData, char** _ppData)
{
	int nLength = _pEndPos - _pStartPos;																//��Ч����

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
	//ʹ��ָ����������н����������ɼ��ݸ��ֳ��ȵ���������Ҫ��

	char* pchEndPos = BufferGetCRLFNearestPtr(_pBuffer_Info);											//���з���ʼ��ַ
	if (pchEndPos == NULL)
		return -1;

	char* pchStartPos = _pBuffer_Info->pStartPtr + _pBuffer_Info->ReadPos;								//��ʼ��ַ
	int nHttpLineLength = pchEndPos - pchStartPos;														//���������ݿ��С

	if (nHttpLineLength <= 0)
		return -1;

#if 0
	//������������������
	int nTypeLength = (char*)memmem(pchStartPos, nHttpLineLength, " ", 1) - pchStartPos;				//����������Ч����
	_pHttpRequest_Info->Type = (char*)calloc(nTypeLength + 1, 1);
	if (_pHttpRequest_Info->Type == NULL)
		return -1;
	strncpy(_pHttpRequest_Info->Type, pchStartPos, nTypeLength);

	pchStartPos += nTypeLength;
	pchStartPos += 1;

	//��������������̬��Դ
	int nUrlLength = (char*)memmem(pchStartPos, nHttpLineLength - nTypeLength, " ", 1) - pchStartPos;	//����̬��Դ��Ч����
	_pHttpRequest_Info->url = (char*)calloc(nUrlLength + 1, 1);
	if (_pHttpRequest_Info->url == NULL)
		return -1;
	strncpy(_pHttpRequest_Info->url, pchStartPos, nUrlLength);

	pchStartPos += nUrlLength;
	pchStartPos += 1;

	//��������������http�汾��
	_pHttpRequest_Info->Version = (char*)calloc(pchEndPos - pchStartPos + 1, 1);
	if (_pHttpRequest_Info->Version == NULL)
		return -1;
	strncpy(_pHttpRequest_Info->Version, pchStartPos, pchEndPos - pchStartPos);
#else
	pchStartPos = SplitRequestLineData(pchStartPos, pchEndPos, " ", &_pHttpRequest_Info->Type);
	pchStartPos = SplitRequestLineData(pchStartPos, pchEndPos, " ", &_pHttpRequest_Info->url);
	SplitRequestLineData(pchStartPos, pchEndPos, NULL, &_pHttpRequest_Info->Version);

#endif
	//Ϊ֮���������ͷ������׼��
	_pBuffer_Info->ReadPos += (nHttpLineLength + 2);
	_pHttpRequest_Info->CurPasreState = PARASEREQHEADERS;

	return 0;
}

int HttpRequestParaseHeader(PHTTPREQUEST_INFO _pHttpRequest_Info, PBUFFER_INFO _pBuffer_Info)
{
	//ʹ��ָ���������ͷ�����������ɼ��ݸ��ֳ��ȵ���������Ҫ��

	char* pchEndPos = BufferGetCRLFNearestPtr(_pBuffer_Info);											//���з���ʼ��ַ
	if (pchEndPos == NULL)
		return -1;

	char* pchStartPos = _pBuffer_Info->pStartPtr + _pBuffer_Info->ReadPos;								//��ʼ��ַ
	int nHttpHeaderLength = pchEndPos - pchStartPos;													//����ͷ���ݿ��С

	char* pchTmp = memmem(pchStartPos, nHttpHeaderLength, ": ", 2);
	int nKeyLength = pchTmp - pchStartPos;																//key����
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
	else //������\r\n��������
	{
		_pBuffer_Info->ReadPos += 2;

		//TODO:�����ڴ˴������Լ���չ����post�����������
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
	//����������� '.' �ַ����粻���ڷ���NULL
	const char* pchDot = strrchr(_FileType, '.');

	if (pchDot == NULL)
		return "text/plain; charset=utf-8";	//���ı�
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
//                <td>������</td>
//                <td>������</td>
//            </tr>
//            <tr>
//                <td>������</td>
//                <td>������</td>
//            </tr>
//        </table>
//    </body>
//</html>

void SendDir(const char* _pDirPath, PBUFFER_INFO _pSendBuf, int _SocketFd)
{
	char* pchFilePath = NULL;										//����������û����ʸ�Ŀ¼�µ��ļ�·��
	int nFilePathLength = 0;										//����������û����ʸ�Ŀ¼�µ��ļ�·������
	char chSendBuf[4096] = { 0 };
	struct dirent** pptdirent = NULL;
	struct stat tstat;
	int nFileNum = scandir(_pDirPath, &pptdirent, NULL, alphasort);	//��ȡָ��Ŀ¼�µ�Ŀ¼��Ϣ

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

		//�ж��ļ�����
		if (S_ISDIR(tstat.st_mode))
		{
			//ƴ��Ŀ¼html��Ϣ
			sprintf(chSendBuf + strlen(chSendBuf),
				"<tr><td><a href=\"%s/\">%s</a></td><td>%d</td></tr>", pptdirent[i]->d_name, pptdirent[i]->d_name, tstat.st_size);
		}
		else
		{
			//ƴ���ļ�html��Ϣ
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
		free(pptdirent[i]);			//scandir����ʱ�����ڲ��������ڴ棬���ͷ�
		pptdirent[i] = NULL;
	}

	sprintf(chSendBuf + strlen(chSendBuf), "</table></body></html>");
	BufferAppendString(_pSendBuf, chSendBuf);
#ifdef MSG_SEND_AUTO
	BufferSocketSend(_pSendBuf, _SocketFd);
#endif // MSG_SEND_AUTO

	free(pptdirent);				//scandir����ʱ�����ڲ��������ڴ棬���ͷ�
	pptdirent = NULL;
}

void SendFile(const char* _pFilePath, PBUFFER_INFO _pSendBuf, int _SocketFd)
{
	int nOpenFd = open(_pFilePath, O_RDONLY);
	assert(nOpenFd > 0);							//���ļ���ʧ�ܵ�ʱ�򣬷�����ֱ���׳��쳣

#if 0	//send�д��û��ռ俽�����ں˵Ĳ�������sendfile������ʽ�������Ϊ��ǰ��ĿΪд�뵽�Լ������Ļ�����������ֻ�ܲ�ȡ�˷�ʽ��
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

			//usleep(1);								//���ͻ��˴������ݵ�ʱ��
		}
		else if (nReadLength == 0)					//�ļ���ȡ���
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
		//sendfileû�д��û��ռ俽�����ں˵Ĳ���
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

	//�����û�����ľ�̬��Դ��Ŀ¼���ļ���
	if (strcmp(_pHttpRequest_Info->url, "/") == 0)
	{
		chFilePath = "./";
	}
	else
	{
		//��Ϊ����ʼ����ʱ���Ѿ�����ǰĿ¼�л����˿ͻ��˷���Ŀ¼�ˣ�����ֱ��ʹ�����·������
		chFilePath = _pHttpRequest_Info->url + 1;

		char* chFilePathTmp = chFilePath;
		DecodeMsg(chFilePath, chFilePathTmp);
	}

	//��ȡ�ļ�����
	struct stat tstat;
	if (stat(chFilePath, &tstat) == -1)
	{
		//�ļ������� -- �ظ�404
		char chTmp[128] = { 0 };

		//״̬�������Ϣ
		_pHttpResponse_Info->StatusCode = NOTFOUND;
		strcpy(_pHttpResponse_Info->StatusMsg, "Not Found");
		strcpy(_pHttpResponse_Info->FileNames, "404.html");

		//��Ӧͷ
		sprintf(chTmp, "%s\r\n", AccordFileType_GetFileMsg(".html"));
		HttpResponseAddHeader(_pHttpResponse_Info, "content-type", chTmp);

		//TODO:�ββ�ƥ��
		_pHttpResponse_Info->SendFuncCallBack = SendFile;
		return 0;
	}

	//�ж��ļ�����
	if (S_ISDIR(tstat.st_mode))
	{
		//�����Ŀ¼��Ϣ�ύ��HttpResponseģ��

		char chTmp[128] = { 0 };
		//״̬�������Ϣ
		_pHttpResponse_Info->StatusCode = OK;
		strcpy(_pHttpResponse_Info->StatusMsg, "OK");

		if (strlen(chFilePath) >= sizeof _pHttpResponse_Info->FileNames)
		{
			perror("�����ļ�·������");
			exit(0);
		}
		strcpy(_pHttpResponse_Info->FileNames, chFilePath);

		//��Ӧͷ
		sprintf(chTmp, "%s", AccordFileType_GetFileMsg(".html"));
		HttpResponseAddHeader(_pHttpResponse_Info, "content-type", chTmp);
		HttpResponseAddHeader(_pHttpResponse_Info, "content-length", "-1");

		//TODO:�ββ�ƥ��
		_pHttpResponse_Info->SendFuncCallBack = SendDir;
	}
	else
	{
		//���ļ������ݷ��͸��ͻ���

		char chTmp[128] = { 0 };
		//״̬�������Ϣ
		_pHttpResponse_Info->StatusCode = OK;
		strcpy(_pHttpResponse_Info->StatusMsg, "OK");

		if (strlen(chFilePath) >= sizeof _pHttpResponse_Info->FileNames)
		{
			perror("�����ļ�·������");
			exit(0);
		}
		strcpy(_pHttpResponse_Info->FileNames, chFilePath);

		//��Ӧͷ
		sprintf(chTmp, "%s", AccordFileType_GetFileMsg(chFilePath));
		HttpResponseAddHeader(_pHttpResponse_Info, "content-type", chTmp);

		memset(chTmp, 0, sizeof chTmp);
		sprintf(chTmp, "%ld", tstat.st_size);
		HttpResponseAddHeader(_pHttpResponse_Info, "content-length", chTmp);

		//TODO:�ββ�ƥ��
		_pHttpResponse_Info->SendFuncCallBack = SendFile;
	}

	return 0;
}
