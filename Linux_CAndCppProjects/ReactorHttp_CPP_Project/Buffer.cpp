//�ļ�������
//      ʵ��һ����д������ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/21
//�޸ļ�¼��
//      2024/2/21     �½�

#include <stdlib.h>
#include <stdio.h>
#include <sys/uio.h> 
#include <arpa/inet.h>
#include <unistd.h>
#define __USE_GNU   
//#include <xlocale.h>
#include <string.h>
#include <iostream>

#include "Buffer.h"

using namespace std;

CBuffer::CBuffer(int _Capcity)
{
	this->m_pchStartPtr = (char*)calloc(_Capcity, sizeof(char));
	if (this->m_pchStartPtr == NULL)
	{
		throw new exception();
	}

	this->m_nCapacity = _Capcity;
	this->m_nReadPos = this->m_nWritePos = 0;
}

CBuffer::~CBuffer()
{
	if (this->m_pchStartPtr == nullptr)
		throw new exception();

	
	free(this->m_pchStartPtr);
}

int CBuffer::SocketRead(int _Fd)
{
	struct iovec tiovecs[2];
	int nCanWriteSize = GetBufferContinuousWriteSize();
	const size_t unRecvBufSize = 40960;											//TODO:�ж�ȡ���ݱ��ضϵ�����

	// ʹ��������д���ڴ棬��ֹ�����ڴ治��ʹ�õ����
	tiovecs[0].iov_base = this->m_pchStartPtr + this->m_nWritePos;
	tiovecs[0].iov_len = nCanWriteSize;
	tiovecs[1].iov_base = malloc(unRecvBufSize);
	tiovecs[1].iov_len = unRecvBufSize;
	if (tiovecs[1].iov_base == NULL)
		return -1;

	int nRecvLength = readv(_Fd, tiovecs, sizeof(tiovecs) / sizeof(tiovecs[0]));
	if (nRecvLength == -1)
		return -1;

	if (nRecvLength <= nCanWriteSize)
	{
		this->m_nWritePos += nCanWriteSize;
	}
	else if (nRecvLength > nCanWriteSize)
	{
		this->m_nWritePos = this->m_nCapacity;
		AppendString((char*)(tiovecs[1].iov_base), nRecvLength - nCanWriteSize);
	}

	//�ͷ���Դ����ֹ�ڴ�й¶
	free(tiovecs[1].iov_base);
	tiovecs[1].iov_base = NULL;

	return nRecvLength;
}

int CBuffer::SocketSend(int _Fd)
{
	int nValidSendLength = GetBufferContinuousReadSize();						//��Ч�Ŀɷ������ݳ���
	int nSendCount = 0;
	if (nValidSendLength > 0)
	{
		nSendCount = send(_Fd, this->m_pchStartPtr + this->m_nReadPos, nValidSendLength, 0);
		if (nSendCount > 0)
		{
			this->m_nReadPos += nSendCount;
			usleep(1);																		//���ͻ��˴������ݵ�ʱ��
			return nSendCount;
		}

	}

	return nSendCount;
}

char* CBuffer::GetCRLFNearestPtr()
{
	return (char*)memmem(this->m_pchStartPtr + this->m_nReadPos, GetBufferContinuousReadSize(), "\r\n", 2);
}

int CBuffer::AppendString(const char* _pData, int _Size)
{
	if (_pData == NULL || _Size <= 0)
		return -1;

	if (CheckBufferWriteSize(_Size) != 0)
		return -1;

	usleep(1);
	memcpy(this->m_pchStartPtr + this->m_nWritePos, _pData, _Size);
	this->m_nWritePos += _Size;

	return 0;
}

int CBuffer::AppendString(const char* _pData)
{
	int nSize = strlen(_pData);

	return AppendString(_pData, nSize);
}

int CBuffer::CheckBufferWriteSize(int _WriteSize)
{
	if (GetBufferContinuousWriteSize() >= _WriteSize)									//��������������д���ڴ��㹻ʹ�õ����
	{
	}
	else if (GetBufferContinuousWriteSize() + this->m_nReadPos >= _WriteSize)		//�����д���ڴ��㹻ʹ�õ����
	{
		//δ���ڴ��С
		int nReadSize = GetBufferContinuousReadSize();

		memcpy(this->m_pchStartPtr, this->m_pchStartPtr + this->m_nReadPos, nReadSize);
		this->m_nReadPos = 0;
		this->m_nWritePos = nReadSize;
	}
	else																							//�����д���ڴ治�㹻ʹ�õ����
	{
		char* pchBuf = (char*)realloc(this->m_pchStartPtr, this->m_nCapacity + _WriteSize);
		if (pchBuf == NULL)
			return -1;

		memset(pchBuf + this->m_nCapacity, 0, _WriteSize);

		this->m_pchStartPtr = pchBuf;
		this->m_nCapacity += _WriteSize;
	}

	return 0;
}
