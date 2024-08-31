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
	//创建socket套接字
	int nFd = socket(AF_INET, SOCK_STREAM, 0);
	if (nFd == -1)
	{
		perror("socket failed.\n");
		return -1;
	}

	//设置端口复用
	int nOptVal = 1;
	int nRet = setsockopt(nFd, SOL_SOCKET, SO_REUSEADDR, &nOptVal, sizeof nOptVal);
	if (nRet == -1)
	{
		perror("setsockopt failed.\n");
		return -1;
	}

	//绑定
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

	//监听（Linux内核最多可同时监听128个套接字）
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
	//创建Epoll根节点
	int nEpFd = epoll_create(1);
	if (nEpFd == -1)
	{
		perror("epoll_create failed.\n");
		return -1;
	}

	//添加节点
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
		//判断被触发的epoll事件
		nEventsNum = epoll_wait(nEpFd, tepoll_events, nEventsSize, -1);

		for (int i = 0; i < nEventsNum; i++)
		{
			PFD_INFO ptFd_Info = (PFD_INFO)malloc(sizeof(FD_INFO));

			if (tepoll_events[i].data.fd == _ServerFd)
			{
				//接收新客户端连接
				ptFd_Info->Fd = _ServerFd;
				ptFd_Info->EpFD = nEpFd;
				pthread_create(&tpthread_t, NULL, AcceptClient, ptFd_Info);
				pthread_detach(tpthread_t);
			}
			else
			{
				//通信
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

	//建立连接
	int nClientFd = accept(pFd_Info->Fd, NULL, NULL);
	if (nClientFd == -1)
	{
		perror("accept failed.\n");
		return NULL;
	}

	//设置套接字为非阻塞模式
	int nFlag = fcntl(nClientFd, F_GETFD);
	nFlag |= O_NONBLOCK;
	fcntl(nClientFd, F_SETFL, nFlag);

	//将客户端套接字添加到epoll节点上
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
	
	//判断数据是否接收完毕
	if (nRecvLength == -1 && errno == EAGAIN)
	{
		//截断请求行数据
		char* pPos = strstr(chTotalBuf, "\r\n");
		chTotalBuf[pPos - chTotalBuf] = '\0';

		//解析http的请求行
		ParseHttpRequestLine(chTotalBuf, pFd_Info->Fd);
	}
	else if (nRecvLength == 0)//客户端断开连接
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
	char chMethods[12] = { 0 };			//存储请求类型
	char chPaths[4096] = { 0 };			//存储请求路径
	char* chFilePath = NULL;

	sscanf(_Line, "%[^ ] %[^ ]", chMethods, chPaths);
	if (strcasecmp(chMethods, "get"))
	{
		return -1;
	}

	//处理用户请求的静态资源（目录或文件）
	if (strcmp(chPaths, "/") == 0)
	{
		chFilePath = "./";
	}
	else
	{
		//因为在起始函数时，已经将当前目录切换到了客户端访问目录了，所有直接使用相对路径即可
		chFilePath = chPaths + 1;

		char* chFilePathTmp = chFilePath;
		DecodeMsg(chFilePath, chFilePathTmp);
	}

	//获取文件属性
	struct stat tstat;
	if (stat(chFilePath, &tstat) == -1)
	{
		//文件不存在 -- 回复404
		SendHeadMsg(_ClientFd, 404, "Not Found", AccordFileType_GetFileMsg(".html"), -1);
		SendFile("404.html", _ClientFd);
		return 0;
	}
	
	//判断文件类型
	if (S_ISDIR(tstat.st_mode))
	{
		//将这个目录发送给客户端
		SendHeadMsg(_ClientFd, 200, "OK", AccordFileType_GetFileMsg(".html"), -1);
		
		SendDir(chFilePath, _ClientFd);
	}
	else
	{
		//将文件的内容发送给客户端
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

int SendDir(const char* _DirPath, int _ClientFd)
{
	char* pchFilePath = NULL;										//完整的相对用户访问根目录下的文件路径
	int nFilePathLength = 0;										//完整的相对用户访问根目录下的文件路径长度
	char chSendBuf[4096] = { 0 };
	struct dirent** pptdirent = NULL;
	struct stat tstat;
	int nFileNum = scandir(_DirPath, &pptdirent, NULL, alphasort);	//获取指定目录下的目录信息

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

		send(_ClientFd, chSendBuf, strlen(chSendBuf), 0);
		memset(chSendBuf, 0, sizeof chSendBuf);
	
		free(pchFilePath);
		pchFilePath = NULL;
		free(pptdirent[i]);			//scandir调用时，在内部会申请内存，需释放
		pptdirent[i] = NULL;
	}

	sprintf(chSendBuf + strlen(chSendBuf), "</table></body></html>");
	send(_ClientFd, chSendBuf, strlen(chSendBuf), 0);

	free(pptdirent);				//scandir调用时，在内部会申请内存，需释放
	pptdirent = NULL;

	return 0;
}

int SendFile(const char* _FilePath, int _ClientFd)
{
	int nOpenFd = open(_FilePath, O_RDONLY);
	assert(nOpenFd > 0);							//当文件打开失败的时候，服务器直接抛出异常

#if 0	//send有从用户空间拷贝到内核的操作，与sendfile相比速率较慢
	int nReadLength = 0;
	char chReadBuf[1024] = { 0 };
	while (1)
	{
		nReadLength = read(nOpenFd, chReadBuf, sizeof chReadBuf);
		if (nReadLength > 0)
		{
			send(_ClientFd, chReadBuf, nReadLength, 0);
			usleep(10);								//给客户端处理数据的时间
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
		sendfile(_ClientFd, nOpenFd, &lOffset, nFileSize - lOffset);
	}
	
#endif

	close(nOpenFd);
	return 0;
}

int SendHeadMsg(int _ClientFd, int _Status, const char* _Descr, const char* _Type, int _Length)
{
	char chBuf[4096] = { 0 };
	//状态行
	sprintf(chBuf, "http/1.1 %d %s\r\n", _Status, _Descr);

	//响应头
	sprintf(chBuf + strlen(chBuf), "content-type: %s\r\n", _Type);
	sprintf(chBuf + strlen(chBuf), "content-length: %d\r\n\r\n", _Length);

	send(_ClientFd, chBuf, strlen(chBuf), 0);
	return 0;
}

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
