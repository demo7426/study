//文件描述：
//      实现一个 观察者（订阅者）模块
//作者：钱锐
//时间：2024/2/27
//修改记录：
//      2024/2/27     新建

#pragma once
#include <iostream>
#include "Publisher.h"

class CAbstractObserver
{
public:
	CAbstractObserver(string _Name, CAbstractPublisher* _pAbstractObserver) : m_strName(_Name), m_pAbstractObserver(_pAbstractObserver)
	{
		_pAbstractObserver->AddObserver(this);
	}
	virtual ~CAbstractObserver() {};

	//解除订阅
	inline void Unsubscribe()
	{
		m_pAbstractObserver->RemoveObserver(this);
	}

	virtual void Updata(string _Msg) = 0;

protected:
	string m_strName;
private:
	CAbstractPublisher* m_pAbstractObserver;
};

class CTeacherObserver : public CAbstractObserver
{
public:
	using CAbstractObserver::CAbstractObserver;
	~CTeacherObserver(){}

	void Updata(string _Msg) override;
};


class CDoctorObserver : public CAbstractObserver
{
public:
	using CAbstractObserver::CAbstractObserver;
	~CDoctorObserver(){}

	void Updata(string _Msg) override;
};


class CNurseObserver : public CAbstractObserver
{
public:
	using CAbstractObserver::CAbstractObserver;
	~CNurseObserver(){}

	void Updata(string _Msg) override;
};

