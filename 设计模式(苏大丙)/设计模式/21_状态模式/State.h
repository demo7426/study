//文件描述：
//      实现一个状态模块
//作者：钱锐
//时间：2024/2/28
//修改记录：
//      2024/2/28     新建

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

