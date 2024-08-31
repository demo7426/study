//文件描述：
//      实现一个建造者/生成器模式（与抽象创建比较复杂的对象时采用）
//作者：钱锐
//时间：2024/1/22
//修改记录：
//      2024/1/22     新建
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class CSunnyShip
{
public:
	CSunnyShip() = default;
	~CSunnyShip() = default;

	void Reset()
	{
		m_vecShipInfo.clear();
	}

	//添加SunnyShip船组件信息
	void AddPart(string _Type)
	{
		m_vecShipInfo.push_back(_Type);
	}

	void PrintfMsg()
	{
		for (const string& item : m_vecShipInfo)
		{
			cout << item << " ";
		}
		cout << endl;
	}
private:
	vector<string> m_vecShipInfo;
};

class CMerryShip
{
public:
	CMerryShip() = default;
	~CMerryShip() = default;

	void Reset()
	{
		m_mapShipInfo.clear();
	}

	//添加MerryShip船组件信息
	void AddAssemble(string _Type, string _Name)
	{
		m_mapShipInfo.insert(make_pair(_Type, _Name));
	}

	void PrintfMsg()
	{
		for (const auto& item : m_mapShipInfo)
		{
			cout << item.first << "：" << item.second << " ";
		}
		cout << endl;
	}
private:
	map<string, string> m_mapShipInfo;
};

//建造者类
class CAbstractBuilder
{
public:
	CAbstractBuilder() {};
	virtual ~CAbstractBuilder() {}

	virtual void Reset() = 0;
	virtual void BuildeShipBody() = 0;
	virtual void BuildeShipWeapon() = 0;
	virtual void BuildeShipEngine() = 0;
	virtual void BuildeShipInterior() = 0;
private:
};

class CSunnyBuilder:public CAbstractBuilder
{
public:
	CSunnyBuilder() {
		m_pcSunnyShip = new CSunnyShip;
	}
	CSunnyBuilder(const CSunnyBuilder& _Item) = delete;
	~CSunnyBuilder() 
	{
		if (m_pcSunnyShip != nullptr)
		{
			delete m_pcSunnyShip;
		}
	}

	void Reset()
	{
		m_pcSunnyShip->Reset();
	}

	void BuildeShipBody()
	{
		m_pcSunnyShip->AddPart("船体：木制 ");
	}

	void BuildeShipWeapon()
	{
		m_pcSunnyShip->AddPart("武器：步枪 ");
	}

	void BuildeShipEngine()
	{
		m_pcSunnyShip->AddPart("引擎：柴油发动机 ");
	}

	void BuildeShipInterior()
	{
		m_pcSunnyShip->AddPart("内饰：简装 ");
	}

	//返回的指针由当前类析构函数释放
	CSunnyShip* GetSunnyShipPtr()
	{
		return m_pcSunnyShip;
	}
private:
	CSunnyShip* m_pcSunnyShip = nullptr;
};

class CMerryBuilder:public CAbstractBuilder
{
public:
	CMerryBuilder() {
		m_pcMerryShip = new CMerryShip;
	}
	CMerryBuilder(const CMerryBuilder& _Item) = delete;
	~CMerryBuilder()
	{
		if (m_pcMerryShip != nullptr)
		{
			delete m_pcMerryShip;
		}
	}

	void Reset()
	{
		m_pcMerryShip->Reset();
	}

	void BuildeShipBody()
	{
		m_pcMerryShip->AddAssemble("船体", "钢铁");
	}

	void BuildeShipWeapon()
	{
		m_pcMerryShip->AddAssemble("武器", "加农炮");
	}

	void BuildeShipEngine()
	{
		m_pcMerryShip->AddAssemble("引擎", "核能发动机");
	}

	void BuildeShipInterior()
	{
		m_pcMerryShip->AddAssemble("内饰", "精装");
	}

	//返回的指针由当前类析构函数释放
	CMerryShip* GetMerryShipPtr()
	{
		return m_pcMerryShip;
	}
private:
	CMerryShip* m_pcMerryShip = nullptr;
};

//指挥类
class CDirectoty
{
public:
	CDirectoty() = delete;
	CDirectoty(const CDirectoty&) = delete;
	CDirectoty(CAbstractBuilder* _AbstractBuilder)
	{
		if (_AbstractBuilder != nullptr)
		{
			m_pcAbstractBuilder = _AbstractBuilder;
		}
	}

	~CDirectoty() = default;

	//建造简单型船
	void BuildSimpleShip()
	{
		m_pcAbstractBuilder->BuildeShipBody();
		m_pcAbstractBuilder->BuildeShipEngine();
	}

	//建造标准型船
	void BuildStandardShip()
	{
		BuildSimpleShip();
		m_pcAbstractBuilder->BuildeShipWeapon();
	}

	//建造旗舰型船
	void BuildRegalShip()
	{
		BuildStandardShip();
		m_pcAbstractBuilder->BuildeShipInterior();
	}

private:
	CAbstractBuilder* m_pcAbstractBuilder = nullptr;
};


//测试创建SunnyShip对象
void TestBuildeSunnyShip()
{
	CAbstractBuilder* pcAbstractBuilder = new CSunnyBuilder;
	CDirectoty cDirectoty(pcAbstractBuilder);

	cDirectoty.BuildSimpleShip();
	CSunnyShip* pcMerryShip = static_cast<CSunnyBuilder*>(pcAbstractBuilder)->GetSunnyShipPtr();
	pcMerryShip->PrintfMsg();

	delete pcAbstractBuilder;
	pcAbstractBuilder = nullptr;
}

//测试创建MerryShip对象
void TestBuildeMerryShip()
{
	CAbstractBuilder* pcAbstractBuilder = new CMerryBuilder;
	CDirectoty cDirectoty(pcAbstractBuilder);

	cDirectoty.BuildStandardShip();
	CMerryShip* pcMerryShip = static_cast<CMerryBuilder*>(pcAbstractBuilder)->GetMerryShipPtr();
	pcMerryShip->PrintfMsg();

	delete pcAbstractBuilder;
	pcAbstractBuilder = nullptr;
}

int main()
{
	TestBuildeSunnyShip();
	TestBuildeMerryShip();

    return 0;
}

