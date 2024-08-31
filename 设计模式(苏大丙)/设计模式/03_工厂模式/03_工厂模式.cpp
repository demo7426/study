//文件描述：
//      实现一个工厂模式（n个简单对象对应n个工厂）
//作者：钱锐
//时间：2024/1/19
//修改记录：
//      2024/1/19     新建
#include <iostream>

using namespace std;

class CAbstractSmile
{
public:
	CAbstractSmile() = default;
	//virtual ~CAbstractSmile() = default;
	virtual ~CAbstractSmile() = 0;	//必须是析构函数成为虚析构函数或者纯虚析构函数、因为当释放子类指针时，如果子类指针指向父类则无法将内存全部释放

	//获取变身信息
	virtual void GetTransformInfo() = 0;
	//获取技能信息
	virtual void GetSkill() = 0;
private:

};

CAbstractSmile::~CAbstractSmile()
{

}

class CLionSmile :public CAbstractSmile
{
public:
	CLionSmile() {};
	~CLionSmile() override {};

	//获取变身信息
	void GetTransformInfo() override
	{
		cout << "可以变身狮子" << '\n';
	}
	//获取技能信息
	void GetSkill() override
	{
		cout << "可以吐出火球" << '\n';
	}

private:

};

class CBatSmile :public CAbstractSmile
{
public:
	CBatSmile() {};
	~CBatSmile() override {};

	//获取变身信息
	void GetTransformInfo() override
	{
		cout << "可以变身蝙蝠" << '\n';
	}
	//获取技能信息
	void GetSkill() override
	{
		cout << "可以操控超声波" << '\n';
	}

private:

};

class CSheepSmile :public CAbstractSmile
{
public:
	CSheepSmile() {};
	~CSheepSmile() override {};

	//获取变身信息
	void GetTransformInfo() override
	{
		cout << "可以变身山羊" << '\n';
	}
	//获取技能信息
	void GetSkill() override
	{
		cout << "可以山羊冲撞" << '\n';
	}

private:

};

enum struct Type :char
{
	SHEEP,
	LION,
	BAT
};

//基类工厂
class CAbstractFactory
{
public:
	CAbstractFactory() = default;
	virtual ~CAbstractFactory() {};

	virtual CAbstractSmile* CreateSmile() = 0;
private:

};

//山羊工厂
class CSheepFactory :public CAbstractFactory
{
public:
	CSheepFactory() = default;
	~CSheepFactory() override {};

	CAbstractSmile* CreateSmile() override
	{
		return new CSheepSmile;
	}
private:

};

//狮子工厂
class CLionFactory :public CAbstractFactory
{
public:
	CLionFactory() = default;
	~CLionFactory() override {};

	CAbstractSmile* CreateSmile() override
	{
		return new CLionSmile;
	}
private:

};

//蝙蝠工厂
class CBatFactory :public CAbstractFactory
{
public:
	CBatFactory() = default;
	~CBatFactory() override {};

	CAbstractSmile* CreateSmile() override
	{
		return new CBatSmile;
	}
private:

};

int main()
{
	CAbstractFactory* pcAbstractFactory = new CLionFactory;
	CAbstractSmile* pcAbstractSmile = pcAbstractFactory->CreateSmile();

	pcAbstractSmile->GetTransformInfo();
	pcAbstractSmile->GetSkill();

	delete pcAbstractFactory;
	delete pcAbstractSmile;

	return 0;
}

