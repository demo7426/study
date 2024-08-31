//文件描述：
//      实现一个代理模式（对同一个基类继承的子类进行代理操作，代理类位于台前，被代理类位于幕后，两者为关联关系）
//作者：钱锐
//时间：2024/2/19
//修改记录：
//      2024/2/19     新建

#include <iostream>

using namespace std;

class CConmunicate
{
public:
	virtual ~CConmunicate() {};
	virtual void Conmunicate() = 0;
};

class CSpeaker : public CConmunicate
{
public:
	~CSpeaker() {};
	void Conmunicate() final
	{
		cout << "Speaker Conmunicate" << endl;
	}
};

class CTelephonid : public CConmunicate
{
public:
	CTelephonid()
	{
		m_bIsStart = true;
		m_pcSpeaker = new CSpeaker;
	}
	~CTelephonid() 
	{
		if (m_pcSpeaker != nullptr)
			delete m_pcSpeaker;
	};

	bool IsStart()
	{
		return m_bIsStart;
	}

	void SetIsStart(bool _Start)
	{
		m_bIsStart = _Start;
	}

	void Conmunicate() final
	{
		cout << "启动电话虫进行翻译以下语句：" << endl;
		m_pcSpeaker->Conmunicate();
	}
private:
	bool m_bIsStart = false;
	CSpeaker* m_pcSpeaker = nullptr;
};

void Test01()
{
	CConmunicate* pcConmunicate = new CSpeaker;
	pcConmunicate->Conmunicate();
	delete pcConmunicate;
	pcConmunicate = nullptr;

	puts("");
	pcConmunicate = new CTelephonid;
	pcConmunicate->Conmunicate();
	delete pcConmunicate;
	pcConmunicate = nullptr;
}


int main()
{
	Test01();
	return 0;
}



