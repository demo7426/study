//文件描述：
//      实现一个桥接模式（将原本放在一个类里面的数据，分离出去，进一步满足设计模式的单一职责原则）
//作者：钱锐
//时间：2024/1/26
//修改记录：
//      2024/1/26     新建

#include <iostream>
#include <map>

using namespace std;

struct _PERSON_INFO
{
	_PERSON_INFO(string _Name, string _Job, string _Ability)
	{
		this->Name = _Name;
		this->Job = _Job;
		this->Ability = _Ability;
	}

	string Name;		//名字
	string Job;			//工作
	string Ability;		//能力
};

class CAbstractTeam
{
public:
	CAbstractTeam(string _Name) : m_TeamName(_Name) {}
	virtual ~CAbstractTeam() {}

	string GetTeamName()											//获取团队名称
	{
		return m_TeamName;
	}

	void AddPeron(struct _PERSON_INFO _Person_Info)					//添加船员
	{
		m_mapPerson_Info.emplace(_Person_Info.Name, _Person_Info);
	}

	void PrintfPersonsInfo()										//打印所有船员信息
	{
		for (const auto& item : m_mapPerson_Info)
		{
			cout << item.second.Name << " " << item.second.Job << " " << item.second.Ability << '\n';
		}
	}

	virtual void ExcuteTask() = 0;

private:
	string m_TeamName;
	map<string, struct _PERSON_INFO> m_mapPerson_Info;
};

//海盗团队
class CPirateTeam:public CAbstractTeam
{
public:
	using CAbstractTeam::CAbstractTeam;
	void ExcuteTask() override
	{
		cout << "烧杀抢掠" << '\n';
	}
private:

};

//官方团队
class CPolicyTeam:public CAbstractTeam
{
public:
	using CAbstractTeam::CAbstractTeam;
	void ExcuteTask() override
	{
		cout << "打击违法犯罪之事" << '\n';
	}
private:

};

class CAbstractShip
{
public:
	CAbstractShip(CAbstractTeam* _pAbstractTeam) : m_pcAbstractTeam(_pAbstractTeam) {}
	virtual ~CAbstractShip() {};

	void PrintfShipInfo()
	{
		this->PrintfShipName();
		this->PrintfShipFeature();

		puts("");
		cout << "团队名称：" << '\n';
		cout << m_pcAbstractTeam->GetTeamName() << '\n';
		cout << "船员信息：" << '\n';
		m_pcAbstractTeam->PrintfPersonsInfo();
		cout << "团队任务：" << '\n';
		m_pcAbstractTeam->ExcuteTask();
	}

private:
	virtual void PrintfShipName() = 0;					//船名
	virtual void PrintfShipFeature() = 0;				//船特点

	CAbstractTeam* m_pcAbstractTeam;
};

class CPariteShip : public CAbstractShip
{
public:
	using CAbstractShip::CAbstractShip;
	~CPariteShip() {};

	void PrintfShipName()
	{
		cout << "梅利海盗船" << '\n';
	}

	void PrintfShipFeature()
	{
		cout << "船头有个羊头" << '\n';
	}

private:

};

class CPolicyShip : public CAbstractShip
{
public:
	using CAbstractShip::CAbstractShip;
	~CPolicyShip() {};

	void PrintfShipName()
	{
		cout << "政府海警船" << '\n';
	}

	void PrintfShipFeature()
	{
		cout << "船头有个加农炮" << '\n';
	}

private:

};

void Test01()
{
	CAbstractTeam* pcAbatract = new CPirateTeam("印度洋海盗团队");
	struct _PERSON_INFO tPersons[]{
		{"xxx00", "船长", "指挥航线"},
		{"xxx01", "厨师", "烹饪料理"},
		{"xxx02", "医师", "治疗疾病"},
	};

	for (int i = 0; i < sizeof(tPersons) / sizeof(tPersons[0]); i++)
		pcAbatract->AddPeron(tPersons[i]);

	CAbstractShip* pcAbstractShip = new CPariteShip(pcAbatract);
	pcAbstractShip->PrintfShipInfo();

	delete pcAbatract;
	delete pcAbstractShip;
}

void Test02()
{
	puts("");
	CAbstractTeam* pcAbatract = new CPolicyTeam("太平洋海警团队");
	struct _PERSON_INFO tPersons[]{
		{"xxx06", "船长", "指挥航线"},
		{"xxx07", "厨师", "烹饪料理"},
		{"xxx08", "医师", "治疗疾病"},
	};

	for (int i = 0; i < sizeof(tPersons) / sizeof(tPersons[0]); i++)
		pcAbatract->AddPeron(tPersons[i]);

	CAbstractShip* pcAbstractShip = new CPolicyShip(pcAbatract);
	pcAbstractShip->PrintfShipInfo();

	delete pcAbatract;
	delete pcAbstractShip;
}

int main()
{
	Test01();
	Test02();

	return 0;
}



