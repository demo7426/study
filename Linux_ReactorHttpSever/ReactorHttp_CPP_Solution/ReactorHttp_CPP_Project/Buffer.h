//文件描述：
//      实现一个读写缓冲区模块
//作者：钱锐
//时间：2024/2/20
//修改记录：
//      2024/2/20     新建
#pragma once

class CBuffer
{
public:
	CBuffer() = delete;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="_Capcity">缓冲区大小</param>
	CBuffer(int _Capcity);
	~CBuffer();

	// 从客户端文件描述符读缓冲区读取数据
	int SocketRead(int _Fd);

	// 将写缓冲区的数据发送到客户端
	int SocketSend(int _Fd);

	// 获取最近的http换行符的内存位置
	char* GetCRLFNearestPtr();

	// 向缓冲区写入数据（带有_Size参数防止写入二进制数据时，遇到'\0'的情况导致数据写入缺失的情况）
	int AppendString(const char* _pData, int _Size);

	// 向缓冲区写入字符串
	int AppendString(const char* _pData);

	inline char* GetStartPtr()
	{
		return m_pchStartPtr;
	}
	
	inline int GetReadPos()
	{
		return m_nReadPos;
	}
	
	inline int SetReadPos(int _ReadPos)
	{
		if (_ReadPos < 0)
			return -1;

		m_nReadPos = _ReadPos;
		return 0;
	}

	//检测缓冲区可连续读取的空间大小
	inline int GetBufferContinuousReadSize()
	{
		//因为在检测写入空间是否够用时，通过内存移动或者扩容，保证了写入位置永远是大于读取位置的，所以返回值直接做差即可
		return this->m_nWritePos - this->m_nReadPos;
	}

private:
	// 检测缓冲区的可写入空间大小是否满足写入数据大小，如果不满足则扩容
	int CheckBufferWriteSize(int _WriteSize);

	//检测缓冲区可连续写入的空间大小
	inline int GetBufferContinuousWriteSize()
	{
		return this->m_nCapacity - this->m_nWritePos;
	}

	
private:
	int m_nCapacity;				//容量
	char* m_pchStartPtr;			//缓冲区起始地址
	int m_nReadPos;				//读位置
	int m_nWritePos;				//写位置
};
