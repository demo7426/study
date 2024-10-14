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
//#define __USE_GNU   
//#include <xlocale.h>
#include <string.h>

#include "HttpRequest.h"
#include "TcpConnection.h"

//�з�����������
static char* SplitRequestLineData(const char* _pStartPos, const char* _pEndPos, const char* _pSerchData, function<void(string)> _Func)
{
	int nLength = _pEndPos - _pStartPos;																//��Ч����

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
	//����������� '.' �ַ����粻���ڷ���NULL
	const char* pchDot = strrchr(_FileType, '.');

	if (pchDot == nullptr)
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

void CHttpRequest::SendDir(const char* _pDirPath, CBuffer* _pSendBuf, int _SocketFd)
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

		_pSendBuf->AppendString(chSendBuf);

#ifdef MSG_SEND_AUTO
		_pSendBuf->SocketSend(_SocketFd);
#endif // MSG_SEND_AUTO

		memset(chSendBuf, 0, sizeof chSendBuf);

		free(pchFilePath);
		pchFilePath = NULL;
		free(pptdirent[i]);			//scandir����ʱ�����ڲ��������ڴ棬���ͷ�
		pptdirent[i] = NULL;
	}

	sprintf(chSendBuf + strlen(chSendBuf), "</table></body></html>");
	_pSendBuf->AppendString(chSendBuf);
#ifdef MSG_SEND_AUTO
	_pSendBuf->SocketSend(_SocketFd);
#endif // MSG_SEND_AUTO

	free(pptdirent);				//scandir����ʱ�����ڲ��������ڴ棬���ͷ�
	pptdirent = NULL;
}

void CHttpRequest::SendFile(const char* _pFilePath, CBuffer* _pSendBuf, int _SocketFd)
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
		case HTTPREQUEST_STATE::PARASEREQLINE:			//��������������
			if (ParaseLine(_pBuffer_Info) != 0)
				return -1;
			break;
		case HTTPREQUEST_STATE::PARASEREQHEADERS:		//��������ͷ����
			if (ParaseHeader(_pBuffer_Info) == -1)
				return -1;
			break;
		case HTTPREQUEST_STATE::PARASEREQBODY:
			//TODO:��ʱû��ʵ��post���������post��������Ҫ������������н���
			this->m_eCurPasreState = HTTPREQUEST_STATE::PARASEREQDONE;
			break;
		case HTTPREQUEST_STATE::PARASEREQDONE:
			break;
		default:
			break;
		}

		// ��Ӧ�ͻ���
		if (this->m_eCurPasreState == HTTPREQUEST_STATE::PARASEREQDONE)
		{
			//����http������׼��http��Ӧ����
			Process(_pHttpResponse_Info);

			//����http״̬�С���Ӧͷ�����С�������
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
	//ʹ��ָ����������н����������ɼ��ݸ��ֳ��ȵ���������Ҫ��

	char* pchEndPos = _pBuffer_Info->GetCRLFNearestPtr();												//���з���ʼ��ַ
	if (pchEndPos == nullptr)
		return -1;

	char* pchStartPos = _pBuffer_Info->GetStartPtr() + _pBuffer_Info->GetReadPos();						//��ʼ��ַ
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
	auto objType = bind(&CHttpRequest::SetType, this, placeholders::_1);
	pchStartPos = SplitRequestLineData(pchStartPos, pchEndPos, " ", objType);

	auto objUrl = bind(&CHttpRequest::Seturl, this, placeholders::_1);
	pchStartPos = SplitRequestLineData(pchStartPos, pchEndPos, " ", objUrl);

	auto objVer = bind(&CHttpRequest::SetVersion, this, placeholders::_1);
	SplitRequestLineData(pchStartPos, pchEndPos, nullptr, objVer);

#endif
	//Ϊ֮���������ͷ������׼��
	_pBuffer_Info->SetReadPos(_pBuffer_Info->GetReadPos()+ nHttpLineLength + 2);
	this->m_eCurPasreState = HTTPREQUEST_STATE::PARASEREQHEADERS;

	return 0;
}

int CHttpRequest::ParaseHeader(CBuffer* _pBuffer_Info)
{
	//ʹ��ָ���������ͷ�����������ɼ��ݸ��ֳ��ȵ���������Ҫ��

	char* pchEndPos = _pBuffer_Info->GetCRLFNearestPtr();												//���з���ʼ��ַ
	if (pchEndPos == nullptr)
		return -1;

	char* pchStartPos = _pBuffer_Info->GetStartPtr() + _pBuffer_Info->GetReadPos();						//��ʼ��ַ
	int nHttpHeaderLength = pchEndPos - pchStartPos;													//����ͷ���ݿ��С

	char* pchTmp = (char*)memmem(pchStartPos, nHttpHeaderLength, ": ", 2);
	int nKeyLength = pchTmp - pchStartPos;																//key����
	if (pchTmp != NULL && nKeyLength != 0)
	{
		this->m_mapHttpHeader.emplace(string(pchStartPos, nKeyLength), string(pchTmp + 2, pchEndPos - (pchTmp + 2)));

		_pBuffer_Info->SetReadPos(_pBuffer_Info->GetReadPos() + nHttpHeaderLength + 2);
}
	else //������\r\n��������
	{
		_pBuffer_Info->SetReadPos(_pBuffer_Info->GetReadPos() + 2);

		//TODO:�����ڴ˴������Լ���չ����post�����������
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

	//�����û�����ľ�̬��Դ��Ŀ¼���ļ���
	if (strcmp(this->m_strUrl.data(), "/") == 0)
	{
		chFilePath = "./";
	}
	else
	{
		//��Ϊ����ʼ����ʱ���Ѿ�����ǰĿ¼�л����˿ͻ��˷���Ŀ¼�ˣ�����ֱ��ʹ�����·������
		chFilePath = this->m_strUrl.data() + 1;

		const char* chFilePathTmp = chFilePath;
		DecodeMsg(const_cast<char*>(chFilePath), const_cast<char*>(chFilePathTmp));
	}

	//��ȡ�ļ�����
	struct stat tstat;
	if (stat(chFilePath, &tstat) == -1)
	{
		//�ļ������� -- �ظ�404
		char chTmp[128] = { 0 };

		//״̬�������Ϣ
		_pHttpResponse_Info->SetStatusCode(HTTPRESPONSE_STATUSCODE::NOTFOUND);
		_pHttpResponse_Info->SetFileName("404.html");

		//��Ӧͷ
		sprintf(chTmp, "%s\r\n", AccordFileType_GetFileMsg(".html"));
		_pHttpResponse_Info->AddHeader("content-type", chTmp);

		//TODO:�ββ�ƥ��
		_pHttpResponse_Info->SetSendFuncCallBack(SendFile);
		return 0;
	}

	//�ж��ļ�����
	if (S_ISDIR(tstat.st_mode))
	{
		//�����Ŀ¼��Ϣ�ύ��HttpResponseģ��

		char chTmp[128] = { 0 };
		//״̬�������Ϣ
		_pHttpResponse_Info->SetStatusCode(HTTPRESPONSE_STATUSCODE::OK);
		_pHttpResponse_Info->SetFileName(chFilePath);

		//��Ӧͷ
		sprintf(chTmp, "%s", AccordFileType_GetFileMsg(".html"));
		_pHttpResponse_Info->AddHeader("content-type", chTmp);
		_pHttpResponse_Info->AddHeader("content-length", "-1");

		//TODO:�ββ�ƥ��
		_pHttpResponse_Info->SetSendFuncCallBack(SendDir);
	}
	else
	{
		//���ļ������ݷ��͸��ͻ���

		//״̬�������Ϣ
		_pHttpResponse_Info->SetStatusCode(HTTPRESPONSE_STATUSCODE::OK);
		_pHttpResponse_Info->SetFileName(chFilePath);

		//��Ӧͷ
		_pHttpResponse_Info->AddHeader("content-type", AccordFileType_GetFileMsg(chFilePath));
		_pHttpResponse_Info->AddHeader("content-length", to_string(tstat.st_size));

		//TODO:�ββ�ƥ��
		_pHttpResponse_Info->SetSendFuncCallBack(SendFile);
	}

	return 0;
}
