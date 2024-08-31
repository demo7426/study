#include <stdlib.h>
#include <stdio.h>
#include <sys/uio.h> 
#include <arpa/inet.h>
#include <unistd.h>
#define __USE_GNU   
#include <xlocale.h>
#include <string.h>

#include "Buffer.h"

PBUFFER_INFO BufferInit(int _Capcity)
{
	PBUFFER_INFO pBuffer_Info = (PBUFFER_INFO)malloc(sizeof(BUFFER_INFO));
	if (pBuffer_Info == NULL)
	{
		return NULL;
	}

	pBuffer_Info->pStartPtr = (char*)calloc(_Capcity, sizeof(char));
	if (pBuffer_Info == NULL)
	{
		free(pBuffer_Info);
		return NULL;
	}

	pBuffer_Info->Capacity = _Capcity;
	pBuffer_Info->ReadPos = pBuffer_Info->WritePos = 0;

	return pBuffer_Info;
}

int BufferDestory(PBUFFER_INFO _pBuffer_Info)
{
	if (_pBuffer_Info == NULL || _pBuffer_Info->pStartPtr == NULL)
		return -1;

	free(_pBuffer_Info->pStartPtr);
	free(_pBuffer_Info);

	return 0;
}

int BufferAppendData(PBUFFER_INFO _pBuffer_Info, const char* _pData, int _Size)
{
	if (_pBuffer_Info == NULL || _pData == NULL || _Size <= 0)
		return -1;

	if (CheckBufferWriteSize(_pBuffer_Info, _Size) != 0)
		return -1;

	usleep(1);
	memcpy(_pBuffer_Info->pStartPtr + _pBuffer_Info->WritePos, _pData, _Size);
	_pBuffer_Info->WritePos += _Size;

	return 0;
}

int BufferAppendString(PBUFFER_INFO _pBuffer_Info, const char* _pData)
{
	int nSize = strlen(_pData);
	
	return BufferAppendData(_pBuffer_Info, _pData, nSize);
}

int BufferSocketRead(PBUFFER_INFO _pBuffer_Info, int _Fd)
{
	struct iovec tiovecs[2];
	int nCanWriteSize = GetBufferContinuousWriteSize(_pBuffer_Info);
	const size_t unRecvBufSize = 40960;											//TODO:有读取数据被截断的隐患

	// 使用两个待写入内存，防止出现内存不够使用的情况
	tiovecs[0].iov_base = _pBuffer_Info->pStartPtr + _pBuffer_Info->WritePos;
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
		_pBuffer_Info->WritePos += nCanWriteSize;
	}
	else if(nRecvLength > nCanWriteSize)
	{
		_pBuffer_Info->WritePos = _pBuffer_Info->Capacity;
		BufferAppendData(_pBuffer_Info, tiovecs[1].iov_base, nRecvLength - nCanWriteSize);
	}

	return nRecvLength;
}

int BufferSocketSend(PBUFFER_INFO _pBuffer_Info, int _Fd)
{
	int nValidSendLength = GetBufferContinuousReadSize(_pBuffer_Info);						//有效的可发送数据长度
	int nSendCount = 0;
	if (nValidSendLength > 0)
	{
		nSendCount = send(_Fd, _pBuffer_Info->pStartPtr + _pBuffer_Info->ReadPos, nValidSendLength, 0);
		if (nSendCount > 0)
		{
			_pBuffer_Info->ReadPos += nSendCount;
			usleep(1);																		//给客户端处理数据的时间
			return nSendCount;
		}

	}

	return nSendCount;
}

char* BufferGetCRLFNearestPtr(PBUFFER_INFO _pBuffer_Info)
{
	if (_pBuffer_Info == NULL)
		return NULL;

	return memmem(_pBuffer_Info->pStartPtr + _pBuffer_Info->ReadPos, GetBufferContinuousReadSize(_pBuffer_Info), "\r\n", 2);
}

int CheckBufferWriteSize(PBUFFER_INFO _pBuffer_Info, int _WriteSize)
{
	if (GetBufferContinuousWriteSize(_pBuffer_Info) >= _WriteSize)									//处理连续可连续写入内存足够使用的情况
	{ }
	else if(GetBufferContinuousWriteSize(_pBuffer_Info) + _pBuffer_Info->ReadPos >= _WriteSize)		//处理可写入内存足够使用的情况
	{
		//未读内存大小
		int nReadSize = GetBufferContinuousReadSize(_pBuffer_Info);

		memcpy(_pBuffer_Info->pStartPtr, _pBuffer_Info->pStartPtr + _pBuffer_Info->ReadPos, nReadSize);
		_pBuffer_Info->ReadPos = 0;
		_pBuffer_Info->WritePos = nReadSize;
	}
	else																							//处理可写入内存不足够使用的情况
	{
		char* pchBuf = (char*)realloc(_pBuffer_Info->pStartPtr, _pBuffer_Info->Capacity + _WriteSize);
		if (pchBuf == NULL)
			return -1;

		memset(pchBuf + _pBuffer_Info->Capacity, 0, _WriteSize);
		 
		_pBuffer_Info->pStartPtr = pchBuf; 
		_pBuffer_Info->Capacity += _WriteSize;
	}

	return 0;
}

int GetBufferContinuousWriteSize(PBUFFER_INFO _pBuffer_Info)
{
	return _pBuffer_Info->Capacity - _pBuffer_Info->WritePos;
}

int GetBufferContinuousReadSize(PBUFFER_INFO _pBuffer_Info)
{
	//因为在检测写入空间是否够用时，通过内存移动或者扩容，保证了写入位置永远是大于读取位置的，所以返回值直接做差即可
	return _pBuffer_Info->WritePos - _pBuffer_Info->ReadPos;
}
