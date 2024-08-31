//文件描述：
//      实现一个享元模式（多个对象共享相同资源时可采用该模式）
//作者：钱锐
//时间：2024/2/19
//修改记录：
//      2024/2/19     新建
#include <iostream>
#include <map>

using namespace std;

/// <summary>
/// 飞翔的重物基类
/// </summary>
class CFlyWeightBody
{
public:
	CFlyWeightBody() = delete;
	CFlyWeightBody(const CFlyWeightBody&) = delete;
	CFlyWeightBody(string _FlyWeightName) : m_strFlyWeightName(_FlyWeightName) {}
	virtual ~CFlyWeightBody() {};

	virtual void Move(int _X, int _Y, int _Speed) = 0;
	virtual void Draw(int _X, int _Y) = 0;
private:
	string m_strFlyWeightName = string();			//物体名称
};

class CShareBombBody : public CFlyWeightBody
{
public:
	using CFlyWeightBody::CFlyWeightBody;
	~CShareBombBody() override {}

	void Move(int _X, int _Y, int _Speed) override
	{
		cout << "普通炸弹移动到了 X=" << _X << " Y=" << _Y << " Speed=" << _Speed << endl;
		Draw(_X, _Y);
	}
	void Draw(int _X, int _Y) override
	{
		cout << "在 X = " << _X << " Y = " << _Y << " 刷新普通炸弹位置" << endl;
	}
};

class CUniqueBombBody : public CFlyWeightBody
{
public:
	using CFlyWeightBody::CFlyWeightBody;
	~CUniqueBombBody() override {}

	void Move(int _X, int _Y, int _Speed) override
	{
		cout << "彩色炸弹移动到了 X=" << _X << " Y=" << _Y << " Speed=" << _Speed << endl;
		Draw(_X, _Y);
	}
	void Draw(int _X, int _Y) override
	{
		cout << "在 X = " << _X << " Y = " << _Y << " 刷新彩色炸弹位置" << endl;
	}
};

class CLanuchBomb
{
public:
	CLanuchBomb() = delete;
	CLanuchBomb(const CLanuchBomb&) = delete;
	CLanuchBomb(CFlyWeightBody* _pFlyWeightBody)
	{
		if (_pFlyWeightBody == nullptr)
			throw new exception("CLanuchBomb构造函数传入参数错误");
		m_pcFlyWeightBody = _pFlyWeightBody;
	}

	void Move(int _X, int _Y, int _Speed)
	{
		this->m_nX = _X;
		this->m_nY = _Y;
		this->m_nSpeed = _Speed;
		m_pcFlyWeightBody->Move(_X, _Y, _Speed);
	}
	void Draw(int _X, int _Y)
	{
		this->m_nX = _X;
		this->m_nY = _Y;
		m_pcFlyWeightBody->Draw(_X, _Y);
	}
private:
	int m_nX = 0;
	int m_nY = 0;
	int m_nSpeed = 100;
	CFlyWeightBody* m_pcFlyWeightBody = nullptr;
};

/// <summary>
/// 炸弹工厂类
/// </summary>
class CBombFactory
{
public:
	/// <summary>
	/// 获取对象，确保名称与炸弹一一对应
	/// </summary>
	/// <param name="_FlyWeightName">炸弹名称</param>
	/// <param name="_Flag">0--普通炸弹指针对象，1--彩色炸弹指针对象</param>
	/// <returns></returns>
	CFlyWeightBody* GetFlyWeightBodyObj(string _FlyWeightName, int _Flag)
	{
		auto item = m_mapFlyWeightBody.find(_FlyWeightName);
		if (item != m_mapFlyWeightBody.end())
		{
			cout << "复用炸弹" << endl;
			return item->second;
		}
		else
		{
			CFlyWeightBody* pcFlyWeightBody = nullptr;
			if (_Flag == 0)
				pcFlyWeightBody = new CShareBombBody(_FlyWeightName);
			else if (_Flag == 1)
				pcFlyWeightBody = new CUniqueBombBody(_FlyWeightName);

			m_mapFlyWeightBody.emplace(_FlyWeightName, pcFlyWeightBody);
			cout << "创建炸弹" << endl;
			return pcFlyWeightBody;
		}
	}

	//销毁所有的炸弹对象
	void Destroy()
	{
		for (auto item : m_mapFlyWeightBody)
		{
			delete item.second;
		}
	}
private:
	map<string, CFlyWeightBody*> m_mapFlyWeightBody;
};

void Test01()
{
	string strBombName[] = { "沙皇-1", "沙皇-1", "沙皇-1", "沙皇-2","沙皇-2","沙皇-3" };
	CBombFactory cBombFactory;

	for (auto item : strBombName)
	{
		CLanuchBomb cLanuchBomb(cBombFactory.GetFlyWeightBodyObj(item, 0));
		for (int i = 0; i < 3; i++)
			cLanuchBomb.Move(rand() % 100, rand() % 50, 1000);
	}
	
	puts("");
	CLanuchBomb cLanuchBomb(cBombFactory.GetFlyWeightBodyObj("沙皇-4", 1));
	for (int i = 0; i < 3; i++)
		cLanuchBomb.Move(rand() % 100, rand() % 50, 1000);
	
	cBombFactory.Destroy();
}

int main()
{
	Test01();
	return 0;
}


