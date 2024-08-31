#pragma once

//////////////////////////////////////////////�ⲿ�ӿ�//////////////////////////////////////////////

// ���������׽���
int InitListenFd(unsigned short _Port);

//����epoll
int EpollRun(int _ServerFd);

////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////�ڲ��ӿ�//////////////////////////////////////////////

//���ӿͻ���
void* AcceptClient(void* _Arg);

//���տͻ��˵�����
void* RecvHttpRequest(void* _Arg);

//����http����������
int ParseHttpRequestLine(const char* _Line, int _ClientFd);

//����Ŀ¼��ָ�����ļ�������
int SendDir(const char* _DirPath, int _ClientFd);

//�����ļ���ָ�����ļ�������
int SendFile(const char* _FilePath, int _ClientFd);

//����http״̬�к���Ӧͷ
int SendHeadMsg(int _ClientFd, int _Status, const char* _Descr, const char* _Type, int _Length);

//�����ļ����ͻ�ȡ�ļ�������Ϣ
const char* AccordFileType_GetFileMsg(const char* _FileType);

//���ַ�ת��Ϊ������
int HexToDec(char _C);

/// <summary>
/// ���룬��http�еĺ�������ת��Ϊlinux��ʶ����ַ�
/// </summary>
/// <param name="_Des">�����ַ���</param>
/// <param name="_Src">�����ַ���</param>
void DecodeMsg(char* _Des, char* _Src);

////////////////////////////////////////////////////////////////////////////////////////////////////

