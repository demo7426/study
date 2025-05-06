/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	LogicSystem.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.05.06
描  述: 实现一个后台逻辑系统
备  注:
修改记录:

  1.  日期: 2025.05.06
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#pragma once

#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <map>

#include "Singleton.h"
#include "MsgNode.h"

class CLogicSystem : public CSingleton<CLogicSystem>
{
	friend class CSingleton<CLogicSystem>;
private:
	CLogicSystem();

	typedef std::function<void(std::shared_ptr<CRecvMsg_Node>)> CallbackFunc;	//回调函数别名

	enum TLV_TYPE			//TLV格式支持的类型ID
	{	
		HELLOWORLD = 1001		
	};

public:
	~CLogicSystem();

	/// <summary>
	/// 添加接收数据节点
	/// </summary>
	/// <param name="_RecvMsg_Node"></param>
	/// <returns></returns>
	int PushBack_RecvMsg_Node(std::shared_ptr<CRecvMsg_Node> _RecvMsg_Node);

private:

	/// <summary>
	/// 线程处理函数
	/// </summary>
	/// <param name=""></param>
	void Thread_Run(void);

	/// <summary>
	/// 注册回调函数
	/// </summary>
	/// <param name=""></param>
	void Register_CallbackFunc(void);

	/// <summary>
	/// Hello world回调函数
	/// </summary>
	/// <param name="_RecvMsg_Node">接收数据节点</param>
	void HelloWorld(std::shared_ptr<CRecvMsg_Node> _RecvMsg_Node);

private:
	std::mutex m_cMutex_Recv;												//接收的互斥锁
	std::condition_variable m_cCondVar_Recv;								//接收的条件变量
	
	bool m_bTheadIsStop = false;											//是否停止线程;false--不停止;true--停止
	std::thread m_cThread;													//处理接收数据的线程

	std::queue<std::shared_ptr<CRecvMsg_Node>> m_queRecv;					//数据接收缓冲队列

	std::map<CLogicSystem::TLV_TYPE, CallbackFunc> m_mapCallbackFunc;		//回调函数map表
};



