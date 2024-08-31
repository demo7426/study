//文件描述：
//      实现一个原型模式（当类内部初始化操作占用资源较多时使用）
//作者：钱锐
//时间：2024/1/23
//修改记录：
//      2024/1/23     新建
#include <iostream>

class CAbstractStudent
{
public:
	virtual ~CAbstractStudent() {}

	virtual CAbstractStudent* Clone() = 0;
	virtual void Printf() = 0;
private:

};

class CStudent01: public CAbstractStudent
{
public:
	~CStudent01() override {} 

	CAbstractStudent* Clone() override
	{
		return new CStudent01(*this);
	}

	void Printf() override
	{
		std::cout << "CStudent01 " << '\n';
	}
private:

};

class CStudent02: public CAbstractStudent
{
public:
	~CStudent02() override {}

	CAbstractStudent* Clone() override
	{
		return new CStudent02(*this);
	}

	void Printf() override
	{
		std::cout << "CStudent02 " << '\n';
	}
private:

};

int main()
{
	CAbstractStudent* pcAbstractStudent01 = new CStudent02;
	CAbstractStudent* pcAbstractStudent02 = pcAbstractStudent01->Clone();

	pcAbstractStudent01->Printf();
	pcAbstractStudent02->Printf();

	delete pcAbstractStudent01;
	delete pcAbstractStudent02;
	pcAbstractStudent01 = nullptr;
	pcAbstractStudent02 = nullptr;
	return 0;
}
