//�ļ�������
//      ʵ��һ������ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/28
//�޸ļ�¼��
//      2024/2/28     �½�
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
	int m_nCurTimeClock;		//��ǰʱ��
	CAbstractState* m_pcAbstractState = nullptr;
};

class CPerson01 : public CAbstractPerson
{
public:
	using CAbstractPerson::CAbstractPerson;
};