//文件描述：
//      实现一个读写缓冲区模块
//作者：钱锐
//时间：2024/1/25
//修改记录：
//      2024/1/25     新建
#pragma once

typedef struct _BUFFER_INFO
{
	int Capacity;				//容量
	char* pStartPtr;			//缓冲区起始地址
	int ReadPos;				//读位置
	int WritePos;				//写位置
}BUFFER_INFO, *PBUFFER_INFO;

// 缓冲区初始化
PBUFFER_INFO BufferInit(int _Capcity);

// 销毁对象
int BufferDestory(PBUFFER_INFO _pBuffer_Info);

// 从客户端文件描述符读缓冲区读取数据
int BufferSocketRead(PBUFFER_INFO _pBuffer_Info, int _Fd);

// 将写缓冲区的数据发送到客户端
int BufferSocketSend(PBUFFER_INFO _pBuffer_Info, int _Fd);

// 获取最近的http换行符的内存位置
char* BufferGetCRLFNearestPtr(PBUFFER_INFO _pBuffer_Info);

// 向缓冲区写入数据（带有_Size参数防止写入二进制数据时，遇到'\0'的情况导致数据写入缺失的情况）
int BufferAppendData(PBUFFER_INFO _pBuffer_Info, const char* _pData, int _Size);

// 向缓冲区写入字符串
int BufferAppendString(PBUFFER_INFO _pBuffer_Info, const char* _pData);

/////////////////////////////////////////内部接口/////////////////////////////////////////

// 检测缓冲区的可写入空间大小是否满足写入数据大小，如果不满足则扩容
int CheckBufferWriteSize(PBUFFER_INFO _pBuffer_Info, int _WriteSize);

//检测缓冲区可连续写入的空间大小
int GetBufferContinuousWriteSize(PBUFFER_INFO _pBuffer_Info);

//检测缓冲区可连续读取的空间大小
int GetBufferContinuousReadSize(PBUFFER_INFO _pBuffer_Info);

//////////////////////////////////////////////////////////////////////////////////////////