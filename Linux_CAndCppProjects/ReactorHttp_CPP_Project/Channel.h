//文件描述：
//      将实现一个响应Channel模块
//作者：钱锐
//时间：2024/2/18
//修改记录：
//      2024/2/18     新建
#pragma once
#include <functional>
//typedef int(*HandleFunc)(void*);
//using HandleFunc = int(*)(void*);

enum class ENUM_FDEVENT :char
{
	TIMEOUT = 0x01,
	READEVENT = 0x02,
	WRITEEVENT = 0x04
};

class CChannel
{
private:
	using HandleFunc = std::function<int(void*)>;
public:
	CChannel() = delete;
	CChannel(const CChannel&) = delete;
	CChannel(int _Fd, enum ENUM_FDEVENT _Events, HandleFunc _ReadCallBack, HandleFunc _WriteCallBack, HandleFunc _DestroyCallBack, void* _Arg);

	HandleFunc m_pReadCallBack;				//读回调函数
	HandleFunc m_pWriteCallBack;			//写回调函数
	HandleFunc m_pDestroyCallBack;			//销毁回调函数

	/// <summary>
	/// 使能写事件
	/// </summary>
	/// <param name="_Status">true--使能; false--取消使能</param>
	void EnableWriteEvent(bool _Status);

	/// <summary>
	/// 检测当前文件描述符的写状态
	/// </summary>
	/// <returns>true--已使能; false--未使能</returns>
	bool IsEnableWriteEvent();

	inline int GetFd()
	{
		return m_nFd;
	}

	inline enum ENUM_FDEVENT GetEvents()
	{
		return m_eEvents;
	}

	inline const void* GetArg()
	{
		return m_pvArg;
	}

private:
	int m_nFd;								//文件描述符
	enum ENUM_FDEVENT m_eEvents;			//事件
	void* m_pvArg;							//回调函数参数
};

