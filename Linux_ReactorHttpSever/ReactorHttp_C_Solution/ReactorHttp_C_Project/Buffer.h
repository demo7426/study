//�ļ�������
//      ʵ��һ����д������ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/25
//�޸ļ�¼��
//      2024/1/25     �½�
#pragma once

typedef struct _BUFFER_INFO
{
	int Capacity;				//����
	char* pStartPtr;			//��������ʼ��ַ
	int ReadPos;				//��λ��
	int WritePos;				//дλ��
}BUFFER_INFO, *PBUFFER_INFO;

// ��������ʼ��
PBUFFER_INFO BufferInit(int _Capcity);

// ���ٶ���
int BufferDestory(PBUFFER_INFO _pBuffer_Info);

// �ӿͻ����ļ�����������������ȡ����
int BufferSocketRead(PBUFFER_INFO _pBuffer_Info, int _Fd);

// ��д�����������ݷ��͵��ͻ���
int BufferSocketSend(PBUFFER_INFO _pBuffer_Info, int _Fd);

// ��ȡ�����http���з����ڴ�λ��
char* BufferGetCRLFNearestPtr(PBUFFER_INFO _pBuffer_Info);

// �򻺳���д�����ݣ�����_Size������ֹд�����������ʱ������'\0'�������������д��ȱʧ�������
int BufferAppendData(PBUFFER_INFO _pBuffer_Info, const char* _pData, int _Size);

// �򻺳���д���ַ���
int BufferAppendString(PBUFFER_INFO _pBuffer_Info, const char* _pData);

/////////////////////////////////////////�ڲ��ӿ�/////////////////////////////////////////

// ��⻺�����Ŀ�д��ռ��С�Ƿ�����д�����ݴ�С�����������������
int CheckBufferWriteSize(PBUFFER_INFO _pBuffer_Info, int _WriteSize);

//��⻺����������д��Ŀռ��С
int GetBufferContinuousWriteSize(PBUFFER_INFO _pBuffer_Info);

//��⻺������������ȡ�Ŀռ��С
int GetBufferContinuousReadSize(PBUFFER_INFO _pBuffer_Info);

//////////////////////////////////////////////////////////////////////////////////////////