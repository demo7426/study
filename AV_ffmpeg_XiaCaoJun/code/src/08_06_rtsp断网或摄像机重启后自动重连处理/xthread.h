/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xthread.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.14
描  述: 线程类实现
备  注:
修改记录:

  1.  日期: 2025.12.14
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#pragma once

#include <mutex>
#include <thread>

struct AVPacket; 

class CXThread
{
public:
	CXThread() = default;
	virtual ~CXThread();

	/// <summary>
	/// 启动线程
	/// </summary>
	/// <param name=""></param>
	/// <returns>-2--线程启动失败(已经有线程在运行);0--线程启动成功;</returns>
	virtual int Start(void);

	/// <summary>
	/// 停止线程
	/// </summary>
	/// <param name=""></param>
	virtual void Stop(void);

	/// <summary>
	/// 责任链设计模式，设置下一个处理对象
	/// </summary>
	/// <param name="_pcXThread">下一个处理对象</param>
	virtual void SetNext(CXThread* _pcXThread) {};

	/// <summary>
	/// 执行下一步
	/// </summary>
	/// <param name=""></param>
	virtual void DoNext(AVPacket* _ptAVPacket) {};

protected:
	/// <summary>
	/// 线程运行函数
	/// </summary>
	/// <param name="_pArg"></param>
	virtual void Main(void) = 0;

protected:
	bool m_IsExit = true;		//线程是否退出标志位;true--退出线程;false--不退出线程

	std::mutex m_cMut;

private:
	std::thread m_cThread;
};
