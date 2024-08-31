//文件描述：
//      实现一个抽象工厂模式（n个复杂对象对应n个工厂）
//作者：钱锐
//时间：2024/1/19
//修改记录：
//      2024/1/19     新建
#include <iostream>

using namespace std;

//抽象船体类
class CAbstractShipBody
{
public:
	CAbstractShipBody() = default;
	virtual ~CAbstractShipBody() {}

	virtual void PrintfShipBodyMsg() = 0;
private:

};

//抽象引擎类
class CAbstractShipEngine
{
public:
	CAbstractShipEngine() = default;
	virtual ~CAbstractShipEngine() {}

	virtual void PrintfShipEngineMsg() = 0;
private:

};

//抽象武器类
class CAbstractShipWeapon
{
public:
	CAbstractShipWeapon() = default;
	virtual ~CAbstractShipWeapon() {}

	virtual void PrintfShipWeaponMsg() = 0;
private:

};

class CWoodShipBody :public CAbstractShipBody
{
public:
	CWoodShipBody() = default;
	~CWoodShipBody() {};

	void PrintfShipBodyMsg() override
	{
		cout << "This ship body is wood..." << '\n';
	}
private:

};

class CIronShipBody :public CAbstractShipBody
{
public:
	CIronShipBody() = default;
	~CIronShipBody() {};

	void PrintfShipBodyMsg() override
	{
		cout << "This ship body is iron..." << '\n';
	}
private:

};

class CAlloyShipBody :public CAbstractShipBody
{
public:
	CAlloyShipBody() = default;
	~CAlloyShipBody() {};

	void PrintfShipBodyMsg() override
	{
		cout << "This ship body is alloy..." << '\n';
	}
private:

};

class COarShipEngine :public CAbstractShipEngine
{
public:
	COarShipEngine() = default;
	~COarShipEngine() override {};

	void PrintfShipEngineMsg() override
	{
		cout << "This ship engine is oar..." << '\n';
	}
private:

};

class CDieselShipEngine :public CAbstractShipEngine
{
public:
	CDieselShipEngine() = default;
	~CDieselShipEngine() override {};

	void PrintfShipEngineMsg() override
	{
		cout << "This ship engine is diesel..." << '\n';
	}
private:

};

class CNuclearShipEngine :public CAbstractShipEngine
{
public:
	CNuclearShipEngine() = default;
	~CNuclearShipEngine() override {};

	void PrintfShipEngineMsg() override
	{
		cout << "This ship engine is nuclear..." << '\n';
	}
private:

};

class CGunShipWeapon :public CAbstractShipWeapon
{
public:
	CGunShipWeapon() = default;
	~CGunShipWeapon() override {};

	void PrintfShipWeaponMsg() override
	{
		cout << "This ship weapon is gun..." << '\n';
	}
private:

};

class CCannonShipWeapon :public CAbstractShipWeapon
{
public:
	CCannonShipWeapon() = default;
	~CCannonShipWeapon() override {};

	void PrintfShipWeaponMsg() override
	{
		cout << "This ship weapon is cannnon..." << '\n';
	}
private:

};

class CLaserShipWeapon :public CAbstractShipWeapon
{
public:
	CLaserShipWeapon() = default;
	~CLaserShipWeapon() override {};

	void PrintfShipWeaponMsg() override
	{
		cout << "This ship weapon is laser..." << '\n';
	}
private:

};

//船类
class CShip
{
public:
	CShip(CAbstractShipBody* _AbstractShipBody, CAbstractShipEngine* _AbstractShipEngine, CAbstractShipWeapon* _AbstractShipWeapon)
	{
		this->m_pcAbstractShipBody = _AbstractShipBody;
		this->m_pcAbstractShipEngine = _AbstractShipEngine;
		this->m_pcAbstractShipWeapon = _AbstractShipWeapon;
	}

	~CShip()
	{
		delete m_pcAbstractShipBody;
		delete m_pcAbstractShipEngine;
		delete m_pcAbstractShipWeapon;
	}

	void PrintfShipMsg()
	{
		this->m_pcAbstractShipBody->PrintfShipBodyMsg();
		this->m_pcAbstractShipEngine->PrintfShipEngineMsg();
		this->m_pcAbstractShipWeapon->PrintfShipWeaponMsg();
	}

private:
	CAbstractShipBody* m_pcAbstractShipBody;
	CAbstractShipEngine* m_pcAbstractShipEngine;
	CAbstractShipWeapon* m_pcAbstractShipWeapon;
};

class CAbstractFactory
{
public:
	CAbstractFactory() = default;
	virtual ~CAbstractFactory() {}

	virtual CShip* CreateShip() = 0;
private:

};

//基础造船工厂
class CBaseShipFactory :public CAbstractFactory
{
public:
	CBaseShipFactory() = default;
	~CBaseShipFactory() override {};

	CShip* CreateShip() override
	{
		return new CShip(new CWoodShipBody, new COarShipEngine, new CGunShipWeapon);
	}
private:

};

//标准造船工厂
class CStandardShipFactory :public CAbstractFactory
{
public:
	CStandardShipFactory() = default;
	~CStandardShipFactory() override {};

	CShip* CreateShip() override
	{
		return new CShip(new CIronShipBody, new CDieselShipEngine, new CCannonShipWeapon);
	}
private:

};

//旗舰造船工厂
class CFlagShipFactory :public CAbstractFactory
{
public:
	CFlagShipFactory() = default;
	~CFlagShipFactory() override {};

	CShip* CreateShip() override
	{
		return new CShip(new CAlloyShipBody, new CNuclearShipEngine, new CLaserShipWeapon);
	}
private:

};


int main()
{
	CAbstractFactory* pcAbstractFactory = new CBaseShipFactory;
	CShip* pcShip = pcAbstractFactory->CreateShip();
	pcShip->PrintfShipMsg();

	delete pcShip;
	delete pcAbstractFactory;
	return 0;
}
