//文件描述：
//      实现一个发布者模块
//作者：钱锐
//时间：2024/2/27
//修改记录：
//      2024/2/27     新建

#pragma once
#include <iostream>
#include <list>

using namespace std;

class CAbstractObserver;

class CAbstractPublisher
{
public:
	virtual ~CAbstractPublisher() {};

	//添加观察者
	int AddObserver(CAbstractObserver* _pAbstractObserver);

	//移除观察者
	int RemoveObserver(CAbstractObserver* _pAbstractObserver);

	virtual int Notify(string _Msg) const  = 0;
protected:
	list<CAbstractObserver*> m_listObserver;
};

class CGossipPublisher : public CAbstractPublisher
{
public:
	~CGossipPublisher() {};
	int Notify(string _Msg) const override;

};

class COfficialPublisher : public CAbstractPublisher
{
public:
	~COfficialPublisher() {};
	int Notify(string _Msg) const override;

};

