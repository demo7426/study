//�ļ�������
//      ʵ��һ������http����ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/26
//�޸ļ�¼��
//      2024/1/26     �½�
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

	// ����
	int Reset();

	// ����http���е��������ݣ����ڲ���Ӧ�ͻ���
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
	// ��ȡ������״̬
	inline auto GetState() -> HTTPREQUEST_STATE const
	{
		return m_eCurPasreState;
	}

	// ���ͷ��ֵ������
	int AddHeader(const string _Key, const string _Value);

	// ��������ͷ���õ�ֵ
	string QueryHeader(const string _Key);
	// �������������ݣ��������Ӧλ��

	int ParaseLine(CBuffer* _pBuffer_Info);

	// ��������ͷ���ݣ��������Ӧλ�ã�ÿ��ֻ�ܽ���һ������
	int ParaseHeader(CBuffer* _pBuffer_Info);

	// http��Ӧ����
	int Process(CHttpResponse* _pHttpResponse_Info);

	void DecodeMsg(char* _Des, char* _Src);

	const char* AccordFileType_GetFileMsg(const char* _FileType);

	static void SendDir(const char* _pDirPath, CBuffer* _pSendBuf, int _SocketFd);

	static void SendFile(const char* _pFilePath, CBuffer* _pSendBuf, int _SocketFd);

	int HexToDec(char _C);
private:
	string m_strType;									//��������
	string m_strUrl;									//���ڴ洢�ͻ��˷���������ʵ���Դ
	string m_strtVersion;								//���ڴ洢�ͻ��˷�����http�汾��
	map<string, string> m_mapHttpHeader;				//���ڴ洢����ͷ��ֵ������
	HTTPREQUEST_STATE m_eCurPasreState;					//��ǰ����״̬
};


