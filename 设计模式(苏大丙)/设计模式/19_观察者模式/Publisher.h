//�ļ�������
//      ʵ��һ��������ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/27
//�޸ļ�¼��
//      2024/2/27     �½�

#pragma once
#include <iostream>
#include <list>

using namespace std;

class CAbstractObserver;

class CAbstractPublisher
{
public:
	virtual ~CAbstractPublisher() {};

	//��ӹ۲���
	int AddObserver(CAbstractObserver* _pAbstractObserver);

	//�Ƴ��۲���
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

