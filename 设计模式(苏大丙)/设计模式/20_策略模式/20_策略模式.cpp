//文件描述：
//      实现一个策略模式（策略与策略之间没有任何关系）
//作者：钱锐
//时间：2024/2/27
//修改记录：
//      2024/2/27     新建

#include <iostream>

using namespace std;

class CAbstractStrategy
{
public:
	virtual ~CAbstractStrategy() {}
	virtual void UseStrategy() = 0;
};

class CWeiWeiJiuZhao : public CAbstractStrategy
{
public:
	void UseStrategy() override
	{
		cout << "使用围魏救赵策略" << endl;
	}
};

class CChenHuoDaJie : public CAbstractStrategy
{
public:
	void UseStrategy() override
	{
		cout << "使用趁火打劫策略" << endl;
	}
};

enum class STRATEGY :char
{
	EASY,
	NORMAL
};

class CGeneral
{
public:
	~CGeneral()
	{
		if (m_pcAbstractStrategy != nullptr)
			delete m_pcAbstractStrategy;
	}

	void Figtht(STRATEGY _Flag)
	{
		if (m_pcAbstractStrategy != nullptr)
			delete m_pcAbstractStrategy;

		switch (_Flag)
		{
		case STRATEGY::EASY:
			m_pcAbstractStrategy = new CWeiWeiJiuZhao;
			break;
		case STRATEGY::NORMAL:
			m_pcAbstractStrategy = new CChenHuoDaJie;
			break;
		default:
			break;
		}

		m_pcAbstractStrategy->UseStrategy();
	}
private:
	CAbstractStrategy* m_pcAbstractStrategy = nullptr;
};

int main()
{
	CGeneral cGeneral;
	cGeneral.Figtht(STRATEGY::NORMAL);

	return 0;
}


