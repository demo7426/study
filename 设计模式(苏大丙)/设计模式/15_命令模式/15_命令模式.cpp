//文件描述：
//      实现一个命令模式（将命令与执行操作拆开，进行解耦操作，易实现一个队列对命令进行同意管理）
//      当前示例实现的为点餐、下单、烹饪案例，以当前餐饮门店柜台前点餐为例
//作者：钱锐
//时间：2024/2/21
//修改记录：
//      2024/2/21     新建

#include <iostream>
#include <map>
#include <list>

using namespace std;

enum class FOODTYPE :char
{
	//中餐类
	MaPoToFu = 0x01,					//麻婆豆腐
	KungPaoChicken,						//宫保鸡丁
	EggplantWithFishFlavor,				//鱼香茄子
	DapanChicken,						//大盘鸡

	//中式面点类
	CrystalCake,						//水晶饼
	CottonCake,							//棉花糕
	MungBeanCake						//绿豆糕
};

//厨师基类
class CAbstractChef
{
public:
	virtual ~CAbstractChef() {};
	virtual void CookFood(FOODTYPE _FoodType) = 0;
};

//中餐大师类
class CChineseMaster : public CAbstractChef
{
public:
	void CookFood(FOODTYPE _FoodType) override
	{
		switch (_FoodType)
		{
		case FOODTYPE::MaPoToFu:
			cout << "中餐大师烹饪麻婆豆腐" << endl;
			break;
		case FOODTYPE::KungPaoChicken:
			cout << "中餐大师烹饪宫保鸡丁" << endl;
			break;
		case FOODTYPE::EggplantWithFishFlavor:
			cout << "中餐大师烹饪鱼香茄子" << endl;
			break;
		case FOODTYPE::DapanChicken:
			cout << "中餐大师烹饪大盘鸡" << endl;
			break;
		default:
			cout << "当前" << (int)_FoodType << "，中餐大师不会制作。" << endl;
			break;
		}
	}
};

//中式面点师类
class CChinesePastryChef : public CAbstractChef
{
public:
	void CookFood(FOODTYPE _FoodType) override
	{
		switch (_FoodType)
		{
		case FOODTYPE::CrystalCake:
			cout << "中式面点师制作水晶饼" << endl;
			break;
		case FOODTYPE::CottonCake:
			cout << "中式面点师制作棉花糕" << endl;
			break;
		case FOODTYPE::MungBeanCake:
			cout << "中式面点师制作绿豆糕" << endl;
			break;
		default:
			cout << "当前" << (int)_FoodType << "，中式面点师不会制作。" << endl;
			break;
		}
	}
};

//订单系统基类
class CAbstractCommand
{
public:
	virtual ~CAbstractCommand() {};

	//向后厨发送烹饪单个食物命令
	virtual void SendCookCommand(FOODTYPE _FoodType) = 0;

protected:
	CAbstractChef* m_pcAbstractChef = nullptr;
};

class CChineseMasterCommand : public CAbstractCommand
{
public:
	CChineseMasterCommand()
	{
		this->m_pcAbstractChef = new CChineseMaster();
		if (this->m_pcAbstractChef == nullptr)
			throw new exception("CChineseMasterCommand 默认构造函数申请内存错误");
	}
	CChineseMasterCommand(const CChineseMasterCommand&) = delete;
	~CChineseMasterCommand()
	{
		if (this->m_pcAbstractChef != nullptr)
			delete this->m_pcAbstractChef;
		this->m_pcAbstractChef = nullptr;
	}

	//向后厨发送烹饪单个食物命令
	void SendCookCommand(FOODTYPE _FoodType)
	{
		this->m_pcAbstractChef->CookFood(_FoodType);
	}
};

class CChinesePastryChefCommand : public CAbstractCommand
{
public:
	CChinesePastryChefCommand()
	{
		this->m_pcAbstractChef = new CChinesePastryChef();
		if (this->m_pcAbstractChef == nullptr)
			throw new exception("CChinesePastryChefCommand 默认构造函数申请内存错误");
	}
	CChinesePastryChefCommand(const CChineseMasterCommand&) = delete;
	~CChinesePastryChefCommand()
	{
		if (this->m_pcAbstractChef != nullptr)
			delete this->m_pcAbstractChef;
		this->m_pcAbstractChef = nullptr;
	}

	//向后厨发送烹饪单个食物命令
	void SendCookCommand(FOODTYPE _FoodType)
	{
		this->m_pcAbstractChef->CookFood(_FoodType);
	}
};

class CWaiter
{
public:
	CWaiter() = default;
	CWaiter(const CWaiter&) = delete;
	~CWaiter()
	{
		delete m_pcAbstractCommand[0];
		delete m_pcAbstractCommand[1];
		m_pcAbstractCommand[0] = nullptr;
		m_pcAbstractCommand[1] = nullptr;
	}

	//加菜
	void AddOrder(int _TableNum, FOODTYPE _FoodType)
	{
		if (m_mapList_Info.find(_TableNum) == m_mapList_Info.end())
		{
			list<FOODTYPE> list{ _FoodType };
			m_mapList_Info.emplace(_TableNum, list);
		}
		else
			m_mapList_Info[_TableNum].push_back(_FoodType);
	}

	//取消菜
	void DeleteOrder(int _TableNum, FOODTYPE _FoodType)
	{
		if (m_mapList_Info.find(_TableNum) != m_mapList_Info.end())
			m_mapList_Info[_TableNum].remove(_FoodType);
	}

	//下单
	int SetOrder(int _TableNum)
	{
		if (m_mapList_Info.find(_TableNum) == m_mapList_Info.end())
			return -1;

		for (auto item : m_mapList_Info[_TableNum])
		{
			switch (item)
			{
			case FOODTYPE::MaPoToFu:
			case FOODTYPE::KungPaoChicken:
			case FOODTYPE::EggplantWithFishFlavor:
			case FOODTYPE::DapanChicken:
				m_pcAbstractCommand[0]->SendCookCommand(item);
				break;
			case FOODTYPE::CrystalCake:
			case FOODTYPE::CottonCake:
			case FOODTYPE::MungBeanCake:
				m_pcAbstractCommand[1]->SendCookCommand(item);
				break;
			default:
				break;
			}
		}
		return 0;
	}

	//结账
	void CheckOut(int _TableNum)
	{
		m_mapList_Info.clear();
	}

private:
	CAbstractCommand* m_pcAbstractCommand[2] = { new CChineseMasterCommand(),  new CChinesePastryChefCommand() };
	map<int, list<FOODTYPE>> m_mapList_Info;		//当前桌订单信息
};

void Test01()
{
	CWaiter cWaiter;
	cWaiter.AddOrder(1, FOODTYPE::MaPoToFu);
	cWaiter.AddOrder(1, FOODTYPE::KungPaoChicken);
	cWaiter.AddOrder(1, FOODTYPE::CottonCake);
	cWaiter.AddOrder(1, FOODTYPE::CrystalCake);
	cWaiter.DeleteOrder(1, FOODTYPE::CrystalCake);

	cWaiter.SetOrder(1);
	cWaiter.CheckOut(1);
}

int main()
{
	Test01();
	return 0;
}


