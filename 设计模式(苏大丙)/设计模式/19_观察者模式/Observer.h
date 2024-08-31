//�ļ�������
//      ʵ��һ�� �۲��ߣ������ߣ�ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/27
//�޸ļ�¼��
//      2024/2/27     �½�

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

	//�������
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

