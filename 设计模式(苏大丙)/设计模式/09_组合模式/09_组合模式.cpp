//文件描述：
//      实现一个组合模式（相同的事物具有类似的字段，采用组合模式，可将其数据结构制作成树结构）
//作者：钱锐
//时间：2024/2/5
//修改记录：
//      2024/2/5     新建
//      2024/2/19    扩展文件描述

#include <iostream>
#include <list>
#include <string>

using namespace std;

//Team基类
class CAbstractTeam
{
public:
	CAbstractTeam() = delete;
	CAbstractTeam(string _Name) : m_strTeamName(_Name){}
	virtual ~CAbstractTeam() {
		cout << "释放" << m_strTeamName << endl;
	}

	void SetParent(CAbstractTeam* _pAbstractTeam)
	{
		m_cParentObj = _pAbstractTeam;
	}
	
	CAbstractTeam* GetParent()
	{
		return m_cParentObj;
	}

	string GetTeamName()
	{
		return m_strTeamName;
	}

	virtual bool IsChild()		//判定是否有子节点
	{
		return false;
	}

	virtual void Add(CAbstractTeam* _pAbstractTeam) {}
	virtual void Remove(CAbstractTeam* _pAbstractTeam) {}
	virtual void Fight() = 0;
	virtual void Display() = 0;

protected:
	string m_strTeamName;							//团队名称
	CAbstractTeam* m_cParentObj = nullptr;			//父类指针对象
};

class CLeafTeam : public CAbstractTeam
{
public:
	using CAbstractTeam::CAbstractTeam;
	~CLeafTeam() {}

	void Fight() override
	{
		cout << "CurTeam: " << m_strTeamName << "与敌人近距离肉身搏斗" << endl;
	}

	void Display() override
	{
		cout << "Parent: " << m_cParentObj->GetTeamName() << "CurTeam: " << m_strTeamName << "Display" << endl;
	}

private:

};

class CManagerTeam : public CAbstractTeam
{
public:
	using CAbstractTeam::CAbstractTeam;
	~CManagerTeam() {}

	bool IsChild() override		//判定是否有子节点
	{
		return true;
	}

	void Add(CAbstractTeam* _pAbstractTeam) 
	{
		m_listTeam.push_back(_pAbstractTeam);
	}

	void Remove(CAbstractTeam* _pAbstractTeam) 
	{
		m_listTeam.remove(_pAbstractTeam);
	}

	void Fight() override
	{
		cout << "CurTeam: " << m_strTeamName << "与敌人远距离战斗" << endl;
	}

	void Display() override
	{
		if (m_cParentObj != nullptr)
			cout << "Parent: " << m_cParentObj->GetTeamName() << ": ";
		else
			cout << "Parent: " << this->GetTeamName() << ": ";

		cout << "CurTeam: " << m_strTeamName << "Display\n";

		cout << endl;
	}

	const list<CAbstractTeam*>& GetListTeam()
	{
		return m_listTeam;
	}

private:
	list<CAbstractTeam*> m_listTeam;
};

//销毁指针对象集其子节点对象
int DestroyAbstractTeam(CAbstractTeam* _pAbstractTeam)
{
	if (_pAbstractTeam == nullptr)
		return -1;

	if (_pAbstractTeam && _pAbstractTeam->IsChild())
	{
		CManagerTeam* pcManagerTeam = dynamic_cast<CManagerTeam*>(_pAbstractTeam);
		list<CAbstractTeam*> listTeam = pcManagerTeam->GetListTeam();

		for (const auto& item : listTeam)
			DestroyAbstractTeam(item);
	}

	delete _pAbstractTeam;
	return 0;
}

int Test01()
{
	CAbstractTeam* pcRootTeam = new CManagerTeam("草帽海贼团");

	string strTeamName[] = { "第一海贼营", "第二海贼营", "第三海贼营" ,"第四海贼营","第五海贼营","第六海贼营" };
	for (int i = 0; i < sizeof strTeamName / sizeof strTeamName[0]; i++)
	{
		CAbstractTeam* pcMiddleTeam = new CManagerTeam(strTeamName[i]);
		pcRootTeam->Add(pcMiddleTeam);
		pcMiddleTeam->SetParent(pcRootTeam);

		if (i == sizeof strTeamName / sizeof strTeamName[0] - 1)
		{
			for (int j = 1; j < 5; j++)
			{
				CAbstractTeam* pcLeafTeam = new CLeafTeam("第" + to_string(j) + "海贼连");
				pcLeafTeam->SetParent(pcMiddleTeam);
				pcMiddleTeam->Add(pcLeafTeam);
				pcLeafTeam->Fight();
				pcLeafTeam->Display();
			}
		}

		pcMiddleTeam->Fight();
		pcMiddleTeam->Display();
	}

	pcRootTeam->Fight();
	pcRootTeam->Display();

	DestroyAbstractTeam(pcRootTeam);
	return 0;
}

int main()
{
	Test01();
	return 0;
}
