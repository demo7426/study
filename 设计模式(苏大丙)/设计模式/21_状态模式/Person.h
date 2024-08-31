//文件描述：
//      实现一个人类模块
//作者：钱锐
//时间：2024/2/28
//修改记录：
//      2024/2/28     新建
#pragma once

#include "State.h"

class CAbstractPerson
{
public:
	virtual ~CAbstractPerson() = 0;

	inline void SetCurTimeClock(int _X)
	{
		SetCAbstractState(new CForenoon);
		m_nCurTimeClock = _X;
	}

	inline int GetCurTimeClock() const
	{
		return m_nCurTimeClock;
	}

	inline void Working()
	{
		m_pcAbstractState->Working(this);
	}

	void SetCAbstractState(CAbstractState* _pAbstractState);

private:
	int m_nCurTimeClock;		//当前时刻
	CAbstractState* m_pcAbstractState = nullptr;
};

class CPerson01 : public CAbstractPerson
{
public:
	using CAbstractPerson::CAbstractPerson;
};