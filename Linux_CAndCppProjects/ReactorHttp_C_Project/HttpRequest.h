//�ļ�������
//      ʵ��һ������http����ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/26
//�޸ļ�¼��
//      2024/1/26     �½�
#pragma once
#include "Buffer.h"
#include "HttpResponse.h"

typedef struct _HTTPHEADER_INFO
{
	char* Key;
	char* Value;
}HTTPHEADER_INFO, *PHTTPHEADER_INFO;

enum HTTPREQUEST_STATE
{
	PARASEREQLINE,
	PARASEREQHEADERS,
	PARASEREQBODY,
	PARASEREQDONE
};


typedef struct _HTTPREQUEST_INFO
{
	char* Type;									//��������
	char* url;									//���ڴ洢�ͻ��˷���������ʵ���Դ
	char* Version;								//���ڴ洢�ͻ��˷�����http�汾��
	PHTTPHEADER_INFO pHttpHeader_Info;			//���ڴ洢����ͷ��ֵ������
	int HttpHeaderValidNum;						//����ͷ����Ч��ֵ�Ը���
	enum HTTPREQUEST_STATE CurPasreState;		//��ǰ����״̬
}HTTPREQUEST_INFO, * PHTTPREQUEST_INFO;

// ��ʼ��
PHTTPREQUEST_INFO HttpRequestInit();

// ����
int HttpRequestReset(PHTTPREQUEST_INFO _pHttpRequest_Info);

// ���ٶ���
int HttpRequestDestory(PHTTPREQUEST_INFO _pHttpRequest_Info);

// ����http���е��������ݣ����ڲ���Ӧ�ͻ���
int HttpRequestParase(PHTTPREQUEST_INFO _pHttpRequest_Info, PBUFFER_INFO _pBuffer_Info,
	PHTTPRESPONSE_INFO _pHttpResponse_Info, PBUFFER_INFO _pSendBuf, int _SocketFd);

/////////////////////////////////////////�ڲ��ӿ�/////////////////////////////////////////

// ��ȡ������״̬
enum HTTPREQUEST_STATE HttpRequestGetState(PHTTPREQUEST_INFO _pHttpRequest_Info);

// ���ͷ��ֵ������
int HttpRequestAddHeader(PHTTPREQUEST_INFO _pHttpRequest_Info, const char* _Key, const char* _Value);

// ��������ͷ���õ�ֵ
char* HttpRequestQueryHeader(PHTTPREQUEST_INFO _pHttpRequest_Info, const char* _Key);

// �������������ݣ��������Ӧλ��
int HttpRequestParaseLine(PHTTPREQUEST_INFO _pHttpRequest_Info, PBUFFER_INFO _pBuffer_Info);

// ��������ͷ���ݣ��������Ӧλ�ã�ÿ��ֻ�ܽ���һ������
int HttpRequestParaseHeader(PHTTPREQUEST_INFO _pHttpRequest_Info, PBUFFER_INFO _pBuffer_Info);

// http��Ӧ����
int HttpRequestProcess(PHTTPREQUEST_INFO _pHttpRequest_Info, PHTTPRESPONSE_INFO _pHttpResponse_Info);
