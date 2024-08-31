//文件描述：
//      实现一个简单工厂模式（n个简单对象对应1个工厂）
//作者：钱锐
//时间：2024/1/18
//修改记录：
//      2024/1/18     新建
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

class CLionSmile:public CAbstractSmile
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

enum struct Type:char
{
	SHEEP,
	LION,
	BAT
};

class CSmileFactory
{
public:
	CSmileFactory() = default;
	~CSmileFactory() = default;

	CAbstractSmile* CreateSmile(Type _Type)
	{
		CAbstractSmile* pcAbstractSmile = nullptr;
		switch (_Type)
		{
		case Type::SHEEP:
			pcAbstractSmile = new CSheepSmile;
			break;
		case Type::LION:
			pcAbstractSmile = new CLionSmile;
			break;
		case Type::BAT:
			pcAbstractSmile = new CBatSmile;
			break;
		default:
			break;
		}
		return pcAbstractSmile;
	}

private:

};

int main()
{
	CSmileFactory cSmileFactory;
	CAbstractSmile* pcAbstractSmile = cSmileFactory.CreateSmile(Type::BAT);
	pcAbstractSmile->GetTransformInfo();
	pcAbstractSmile->GetSkill();

	delete pcAbstractSmile;
    return 0;
}

