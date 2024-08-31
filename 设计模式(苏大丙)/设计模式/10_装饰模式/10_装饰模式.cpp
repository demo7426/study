//文件描述：
//      实现一个装饰模式（用于对一个事物进行装饰，丰富其字段相关信息）
//作者：钱锐
//时间：2024/2/18
//修改记录：
//      2024/2/18     新建
//      2024/2/19     扩展文件描述
#include <iostream>

using namespace std;

class CSoldier
{
public:
	CSoldier() = default;
	CSoldier(string _Name) :m_strName(_Name) {}
	virtual ~CSoldier() {}

	string GetName()
	{
		return m_strName;
	}

	//战斗
	virtual void Fight() = 0;

protected:
	string m_strName = string();
};

class CPerson :public CSoldier
{
public:
	using CSoldier::CSoldier;
	~CPerson() = default;
	
	void Fight() final
	{
		cout << this->GetName() << "使用体术进行战斗。" << endl;
	}
private:

};

class CDecoration :public CSoldier
{
public:
	CDecoration() = default;
	~CDecoration() = default;

	//装饰
	void Decorate(CSoldier* _pSoldier)
	{
		this->m_pcSoldier = _pSoldier;
		this->m_strName = _pSoldier->GetName();
	}

protected:
	CSoldier* m_pcSoldier = nullptr;
};

class CDarkDecoration : public CDecoration
{
public:
	CDarkDecoration() = default;
	~CDarkDecoration() = default;

	void Fight() final
	{
		m_pcSoldier->Fight();
		cout << this->GetName() << "使用黑洞超能力进行战斗。" << endl;
	}
};

class CQuakeDecoration : public CDecoration
{
public:
	CQuakeDecoration() = default;
	~CQuakeDecoration() = default;

	void Fight() final
	{
		m_pcSoldier->Fight();
		cout << this->GetName() << "使用震动超能力进行战斗。" << endl;
	}
};

class CLaserDecoration : public CDecoration
{
public:
	CLaserDecoration() = default;
	~CLaserDecoration() = default;

	void Fight() final
	{
		m_pcSoldier->Fight();
		cout << this->GetName() << "使用激光超能力进行战斗。" << endl;
	}
};

//测试函数
void Test01()
{
	CSoldier* pcSoldier = new CPerson("战士");
	CDecoration* pcDecoration01 = new CDarkDecoration();
	CDecoration* pcDecoration02 = new CQuakeDecoration();
	CDecoration* pcDecoration03 = new CLaserDecoration();

	//装饰
	pcDecoration01->Decorate(pcSoldier);
	pcDecoration02->Decorate(pcDecoration01);
	pcDecoration03->Decorate(pcDecoration02);
	pcDecoration03->Fight();

	delete pcDecoration03;
	delete pcDecoration02;
	delete pcDecoration01;
	delete pcSoldier;
}

int main()
{
	Test01();
    return 0;
}
