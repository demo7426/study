//�ļ�������
//      ʵ��һ��״̬ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/28
//�޸ļ�¼��
//      2024/2/28     �½�

#pragma once
#include <iostream>

class CAbstractPerson;

class CAbstractState
{
public:
	virtual ~CAbstractState() {};
	virtual void Working(CAbstractPerson* _pAbstractPerson) = 0;
};

class CForenoon : public CAbstractState
{
public:
	void Working(CAbstractPerson* _pAbstractPerson) override;
};

class Cnoon : public CAbstractState
{
public:
	void Working(CAbstractPerson* _pAbstractPerson) override;
};

class CAfternoon : public CAbstractState
{
public:
	void Working(CAbstractPerson* _pAbstractPerson) override;
};

class CEvening : public CAbstractState
{
public:
	void Working(CAbstractPerson* _pAbstractPerson) override;
};

