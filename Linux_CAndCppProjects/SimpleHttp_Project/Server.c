#include "Server.h"

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <assert.h>
#include <sys/sendfile.h>
#include <dirent.h>
#include <ctype.h>
#include <pthread.h>

#define __USE_BSD
#include <unistd.h>

typedef struct _FD_INFO
{
	int Fd;
	int EpFD;
}FD_INFO, *PFD_INFO;

int InitListenFd(unsigned short _Port)
{
	//����socket�׽���
	int nFd = socket(AF_INET, SOCK_STREAM, 0);
	if (nFd == -1)
	{
		perror("socket failed.\n");
		return -1;
	}

	//���ö˿ڸ���
	int nOptVal = 1;
	int nRet = setsockopt(nFd, SOL_SOCKET, SO_REUSEADDR, &nOptVal, sizeof nOptVal);
	if (nRet == -1)
	{
		perror("setsockopt failed.\n");
		return -1;
	}

	//��
	struct sockaddr_in tsockaddr_in;
	tsockaddr_in.sin_family = AF_INET;
	tsockaddr_in.sin_port = htons(_Port);
	tsockaddr_in.sin_addr.s_addr = INADDR_ANY;

	nRet = bind(nFd, (const struct sockaddr*)&tsockaddr_in, sizeof tsockaddr_in);
	if (nRet == -1)
	{
		perror("bind failed.\n");
		return -1;
	}

	//������Linux�ں�����ͬʱ����128���׽��֣�
	nRet = listen(nFd, 128);
	if (nRet == -1)
	{
		perror("listen failed.\n");
		return -1;
	}

	return nFd;
}

int EpollRun(int _ServerFd)
{
	//����Epoll���ڵ�
	int nEpFd = epoll_create(1);
	if (nEpFd == -1)
	{
		perror("epoll_create failed.\n");
		return -1;
	}

	//��ӽڵ�
	struct epoll_event tepoll_event;
	tepoll_event.events = EPOLLIN;
	tepoll_event.data.fd = _ServerFd;

	if (epoll_ctl(nEpFd, EPOLL_CTL_ADD, _ServerFd, &tepoll_event) == -1)
	{
		perror("epoll_ctl failed.\n");
		return -1;
	}

	struct epoll_event tepoll_events[1024];
	int nEventsSize = sizeof(tepoll_events) / sizeof(tepoll_events[0]);
	int nEventsNum = 0;
	pthread_t tpthread_t;

	while (1)
	{
		//�жϱ�������epoll�¼�
		nEventsNum = epoll_wait(nEpFd, tepoll_events, nEventsSize, -1);

		for (int i = 0; i < nEventsNum; i++)
		{
			PFD_INFO ptFd_Info = (PFD_INFO)malloc(sizeof(FD_INFO));

			if (tepoll_events[i].data.fd == _ServerFd)
			{
				//�����¿ͻ�������
				ptFd_Info->Fd = _ServerFd;
				ptFd_Info->EpFD = nEpFd;
				pthread_create(&tpthread_t, NULL, AcceptClient, ptFd_Info);
				pthread_detach(tpthread_t);
			}
			else
			{
				//ͨ��
				ptFd_Info->Fd = tepoll_events[i].data.fd;
				ptFd_Info->EpFD = nEpFd;
				pthread_create(&tpthread_t, NULL, RecvHttpRequest, ptFd_Info);
				pthread_detach(tpthread_t);
			}
		}
	}

	return 0;
}

void* AcceptClient(void* _Arg)
{
	PFD_INFO pFd_Info = (PFD_INFO)_Arg;

	//��������
	int nClientFd = accept(pFd_Info->Fd, NULL, NULL);
	if (nClientFd == -1)
	{
		perror("accept failed.\n");
		return NULL;
	}

	//�����׽���Ϊ������ģʽ
	int nFlag = fcntl(nClientFd, F_GETFD);
	nFlag |= O_NONBLOCK;
	fcntl(nClientFd, F_SETFL, nFlag);

	//���ͻ����׽�����ӵ�epoll�ڵ���
	struct epoll_event tepoll_event;
	tepoll_event.events = EPOLLIN | EPOLLET;
	tepoll_event.data.fd = nClientFd;

	if (epoll_ctl(pFd_Info->EpFD, EPOLL_CTL_ADD, nClientFd, &tepoll_event) == -1)
	{
		perror("epoll_ctl failed.\n");
		return NULL;
	}

	return NULL;
}

void* RecvHttpRequest(void* _Arg)
{
	PFD_INFO pFd_Info = (PFD_INFO)_Arg;
	char chTotalBuf[4096] = {0};
	char chTmpBuf[512] = { 0 };
	int nPos = 0, nRecvLength = 0;

	while ((nRecvLength = recv(pFd_Info->Fd, chTmpBuf, sizeof chTmpBuf, 0)) > 0)
	{
		if (nPos + nRecvLength < sizeof chTotalBuf)
		{
			memcpy(chTotalBuf + nPos, chTmpBuf, nRecvLength);
		}
		nPos += nRecvLength;
		memset(chTmpBuf, 0, sizeof chTmpBuf);
	}
	
	//�ж������Ƿ�������
	if (nRecvLength == -1 && errno == EAGAIN)
	{
		//�ض�����������
		char* pPos = strstr(chTotalBuf, "\r\n");
		chTotalBuf[pPos - chTotalBuf] = '\0';

		//����http��������
		ParseHttpRequestLine(chTotalBuf, pFd_Info->Fd);
	}
	else if (nRecvLength == 0)//�ͻ��˶Ͽ�����
	{
		epoll_ctl(pFd_Info->EpFD, EPOLL_CTL_DEL, pFd_Info->Fd, NULL);
		close(pFd_Info->Fd);
	}
	else
	{
		perror("recv failed.\n");
	}

	return NULL;
}

int ParseHttpRequestLine(const char* _Line, int _ClientFd)
{
	char chMethods[12] = { 0 };			//�洢��������
	char chPaths[4096] = { 0 };			//�洢����·��
	char* chFilePath = NULL;

	sscanf(_Line, "%[^ ] %[^ ]", chMethods, chPaths);
	if (strcasecmp(chMethods, "get"))
	{
		return -1;
	}

	//�����û�����ľ�̬��Դ��Ŀ¼���ļ���
	if (strcmp(chPaths, "/") == 0)
	{
		chFilePath = "./";
	}
	else
	{
		//��Ϊ����ʼ����ʱ���Ѿ�����ǰĿ¼�л����˿ͻ��˷���Ŀ¼�ˣ�����ֱ��ʹ�����·������
		chFilePath = chPaths + 1;

		char* chFilePathTmp = chFilePath;
		DecodeMsg(chFilePath, chFilePathTmp);
	}

	//��ȡ�ļ�����
	struct stat tstat;
	if (stat(chFilePath, &tstat) == -1)
	{
		//�ļ������� -- �ظ�404
		SendHeadMsg(_ClientFd, 404, "Not Found", AccordFileType_GetFileMsg(".html"), -1);
		SendFile("404.html", _ClientFd);
		return 0;
	}
	
	//�ж��ļ�����
	if (S_ISDIR(tstat.st_mode))
	{
		//�����Ŀ¼���͸��ͻ���
		SendHeadMsg(_ClientFd, 200, "OK", AccordFileType_GetFileMsg(".html"), -1);
		
		SendDir(chFilePath, _ClientFd);
	}
	else
	{
		//���ļ������ݷ��͸��ͻ���
		SendHeadMsg(_ClientFd, 200, "OK", AccordFileType_GetFileMsg(chFilePath), tstat.st_size);
		SendFile(chFilePath, _ClientFd);
	}

	return 0;
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

int SendDir(const char* _DirPath, int _ClientFd)
{
	char* pchFilePath = NULL;										//����������û����ʸ�Ŀ¼�µ��ļ�·��
	int nFilePathLength = 0;										//����������û����ʸ�Ŀ¼�µ��ļ�·������
	char chSendBuf[4096] = { 0 };
	struct dirent** pptdirent = NULL;
	struct stat tstat;
	int nFileNum = scandir(_DirPath, &pptdirent, NULL, alphasort);	//��ȡָ��Ŀ¼�µ�Ŀ¼��Ϣ

	sprintf(chSendBuf, "<html><head><title>%s</title></head><body><table>", _DirPath);

	sprintf(chSendBuf + strlen(chSendBuf),
		"<tr><td>%s</td><td>%s</td></tr>", "FileName", "Size");

	for (int i = 0; i < nFileNum; i++)
	{
#if 1
		printf("%s\n", pptdirent[i]->d_name);
#endif // _QR_DBG

		nFilePathLength = strlen(pptdirent[i]->d_name) + strlen(_DirPath) + 2;
		pchFilePath = (char*)malloc(nFilePathLength);
		memset(pchFilePath, 0, nFilePathLength);
		sprintf(pchFilePath, "%s/%s", _DirPath, pptdirent[i]->d_name);

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

		send(_ClientFd, chSendBuf, strlen(chSendBuf), 0);
		memset(chSendBuf, 0, sizeof chSendBuf);
	
		free(pchFilePath);
		pchFilePath = NULL;
		free(pptdirent[i]);			//scandir����ʱ�����ڲ��������ڴ棬���ͷ�
		pptdirent[i] = NULL;
	}

	sprintf(chSendBuf + strlen(chSendBuf), "</table></body></html>");
	send(_ClientFd, chSendBuf, strlen(chSendBuf), 0);

	free(pptdirent);				//scandir����ʱ�����ڲ��������ڴ棬���ͷ�
	pptdirent = NULL;

	return 0;
}

int SendFile(const char* _FilePath, int _ClientFd)
{
	int nOpenFd = open(_FilePath, O_RDONLY);
	assert(nOpenFd > 0);							//���ļ���ʧ�ܵ�ʱ�򣬷�����ֱ���׳��쳣

#if 0	//send�д��û��ռ俽�����ں˵Ĳ�������sendfile������ʽ���
	int nReadLength = 0;
	char chReadBuf[1024] = { 0 };
	while (1)
	{
		nReadLength = read(nOpenFd, chReadBuf, sizeof chReadBuf);
		if (nReadLength > 0)
		{
			send(_ClientFd, chReadBuf, nReadLength, 0);
			usleep(10);								//���ͻ��˴������ݵ�ʱ��
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
		sendfile(_ClientFd, nOpenFd, &lOffset, nFileSize - lOffset);
	}
	
#endif

	close(nOpenFd);
	return 0;
}

int SendHeadMsg(int _ClientFd, int _Status, const char* _Descr, const char* _Type, int _Length)
{
	char chBuf[4096] = { 0 };
	//״̬��
	sprintf(chBuf, "http/1.1 %d %s\r\n", _Status, _Descr);

	//��Ӧͷ
	sprintf(chBuf + strlen(chBuf), "content-type: %s\r\n", _Type);
	sprintf(chBuf + strlen(chBuf), "content-length: %d\r\n\r\n", _Length);

	send(_ClientFd, chBuf, strlen(chBuf), 0);
	return 0;
}

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

int HexToDec(char _C)
{
	if (_C >= '0' && _C <= '9')
		return _C - '0';
	else if (_C >= 'a' && _C <= 'f')
		return _C - 'a' + 10;
	else if (_C >= 'A' && _C <= 'F')
		return _C - 'A' + 10;

	return 0;
}

void DecodeMsg(char* _Des, char* _Src)
{
	for (;*_Src != '\0'; ++_Src, ++_Des)
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
