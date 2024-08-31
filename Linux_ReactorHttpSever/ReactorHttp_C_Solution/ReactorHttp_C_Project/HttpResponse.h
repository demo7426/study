//�ļ�������
//      ʵ��һ����Ӧhttp����ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/30
//�޸ļ�¼��
//      2024/1/30     �½�
#pragma once
#include "Buffer.h"

enum HTTPRESPONSE_STATUSCODE
{
	UNKNOWN,
	OK = 200,					//���ճɹ�
	MOVEDPERMANENTLY = 301,		//�����ض���
	MOVEDTEMPORARILY = 302,		//��ʱ�ض���
	BADREQUEST = 400,			//���������
	NOTFOUND = 404				//û���ҵ���Ӧ���ļ�·��
};

// ��ֵ��
struct _HTTPRESQPOSE_HEADER_INFO
{
	//TODO:httpЭ���ڲ�����ͷ��Ϣ�ļ�ֵ����Ϣ��Խ����գ����ڿ��Զ���������
	char Key[32];				//��
	char Value[128];			//ֵ
};

typedef void (*HttpResponseFunc)(const char* _pFileName, PBUFFER_INFO _pSendBuf, int _SocketFd);

typedef struct _HTTPRESPONSE_INFO
{
	//״̬�У�״̬�롢״̬��Ϣ
	enum HTTPRESPONSE_STATUSCODE StatusCode;				//״̬��
	char StatusMsg[128];									//״̬��Ϣ

	//��Ӧͷ
	struct _HTTPRESQPOSE_HEADER_INFO* pHttpHeaders;			//��Ӧͷ��ֵ����Ϣ
	int HeadersValidNum;									//��Ӧͷ��ֵ����Ч����

	char FileNames[2048];									//�ļ�·��
	HttpResponseFunc SendFuncCallBack;						//����http��Ӧ���ݻص�����
}HTTPRESPONSE_INFO, *PHTTPRESPONSE_INFO;

//��ʼ��
PHTTPRESPONSE_INFO HttpResponseInit();

//����
int HttpResponseDestroy(PHTTPRESPONSE_INFO _pHttpResponse_Info);

//��Ӽ�ֵ��
int HttpResponseAddHeader(PHTTPRESPONSE_INFO _pHttpResponse_Info, const char* _pKey, const char* _pValue);

//��http�������С�����ͷд�뵽���ͻ����� _pSendBuf
int HttpResponsePrepareMsg(PHTTPRESPONSE_INFO _pHttpResponse_Info, PBUFFER_INFO _pSendBuf, int _SocketFd);
