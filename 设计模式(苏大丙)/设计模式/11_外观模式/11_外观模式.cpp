//文件描述：
//      实现一个外观模式（用于简化接口时使用，对复杂的接口调用进行二次封装）
//作者：钱锐
//时间：2024/2/18
//修改记录：
//      2024/2/18     新建
//      2024/2/19     扩展文件描述
#include <iostream>

using namespace std;

class CCoke
{
public:
	void ImitCoke()
	{
		cout << "注入可乐" << endl;
	}
};

class CEnergyConver
{
public:
	void EnergyConver()
	{
		cout << "将可乐转换为特殊能量" << endl;
	}
};

class CAimAndLock
{
public:
	void AimAndLock()
	{
		cout << "瞄准和锁定敌人" << endl;
	}
};

class CConnon
{
public:
	void ConnonFire()
	{
		cout << "加农炮发射" << endl;
	}
};

class CWindConnon
{
public:
	void WindConnonFire()
	{
		cout << "风来炮发射，使用反作用力稳定船身" << endl;
	}
};

class CLionConnon
{
public:
	CLionConnon()
	{
		m_pcCoke = new CCoke;
		m_pcEnergyConver = new CEnergyConver;
		m_pcAimAndLock = new CAimAndLock;
		m_pcConnon = new CConnon;
		m_pcWindConnon = new CWindConnon;
	}
	CLionConnon(const CLionConnon&) = delete;

	~CLionConnon()
	{
		delete m_pcCoke;
		delete m_pcEnergyConver;
		delete m_pcAimAndLock;
		delete m_pcConnon;
		delete m_pcWindConnon;

		m_pcCoke = nullptr;
		m_pcEnergyConver = nullptr;
		m_pcAimAndLock = nullptr;
		m_pcConnon = nullptr;
		m_pcWindConnon = nullptr;
	}

	//瞄准和锁定敌人
	void AimAndLock()
	{
		m_pcCoke->ImitCoke();
		m_pcEnergyConver->EnergyConver();
		m_pcAimAndLock->AimAndLock();
	}

	//发射
	void Fire()
	{
		m_pcConnon->ConnonFire();
		m_pcWindConnon->WindConnonFire();
	}

private:
	CCoke* m_pcCoke = nullptr;
	CEnergyConver* m_pcEnergyConver = nullptr;
	CAimAndLock* m_pcAimAndLock = nullptr;
	CConnon* m_pcConnon = nullptr;
	CWindConnon* m_pcWindConnon = nullptr;
};

int main(int argc, char* argv[], char* envp[])
{
	CLionConnon* pcLionConnon = new CLionConnon();

	pcLionConnon->AimAndLock();
	pcLionConnon->Fire();

	delete pcLionConnon;
	pcLionConnon = nullptr;

	return 0;
}