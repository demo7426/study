//文件描述：
//      实现一个责任链模式（适用于需要一层一层的审批或判定的情况）
//      当前示例实现的为单向链表的数据结构，可以拓展为双向链表、树、图数据结构等
//作者：钱锐
//时间：2024/2/20
//修改记录：
//      2024/2/20     新建

#include <iostream>

using namespace std;

enum class REQUEST:char
{
	ASKFORLEAVE = 0x01,		//请假
	RAISESALARY,			//涨薪
	RESIGN					//辞职
};

class CAbstractManager
{
public:
	CAbstractManager() = delete;

	/// <summary>
	/// 自定义设置下一个链表节点构造函数
	/// </summary>
	/// <param name="_pNext">下一个链表节点，值可以为nullptr</param>
	CAbstractManager(CAbstractManager* _pNext) : m_pcNext(_pNext) {}
	virtual ~CAbstractManager(){}

	//提交请求
	virtual void HandleRequest(REQUEST _Request) const = 0;
protected:
	CAbstractManager* m_pcNext = nullptr;
};

class CManager : public CAbstractManager
{
public:
	using CAbstractManager::CAbstractManager;
	void HandleRequest(REQUEST _Request) const override
	{
		switch (_Request)
		{
		case REQUEST::ASKFORLEAVE:
			cout << "同意请假，好好休息..." << endl;
			break;
		case REQUEST::RAISESALARY:
			cout << "没有同意涨薪权限，向上级提交请求... ======>>";
			m_pcNext->HandleRequest(REQUEST::RAISESALARY);
			break;
		case REQUEST::RESIGN:
			cout << "没有同意辞职权限，向上级提交请求... ======>>";
			m_pcNext->HandleRequest(REQUEST::RESIGN);
			break;
		default:
			break;
		}
	}
};

class CCEO : public CAbstractManager
{
public:
	using CAbstractManager::CAbstractManager;
	void HandleRequest(REQUEST _Request) const override
	{
		switch (_Request)
		{
		case REQUEST::ASKFORLEAVE:
			cout << "同意请假，好好休息..." << endl;
			break;
		case REQUEST::RAISESALARY:
			cout << "同意涨薪，加两千元的基础薪资..." << endl;
			break;
		case REQUEST::RESIGN:
			cout << "没有同意辞职权限，向上级提交请求... ======>>";
			m_pcNext->HandleRequest(REQUEST::RESIGN);
			break;
		default:
			break;
		}
	}
};

class CBOSS : public CAbstractManager
{
public:
	using CAbstractManager::CAbstractManager;
	void HandleRequest(REQUEST _Request) const override
	{
		switch (_Request)
		{
		case REQUEST::ASKFORLEAVE:
			cout << "不同意请假，好好工作..." << endl;
			break;
		case REQUEST::RAISESALARY:
			cout << "不同意涨薪，现在薪水已经够高了..." << endl;
			break;
		case REQUEST::RESIGN:
			cout << "不同意辞职，公司需要你..." << endl;
			break;
		default:
			break;
		}
	}
};

class CEmployee
{
public:
	void SubmitRequest(CAbstractManager* _pAbstractManager, REQUEST _Request)
	{
		_pAbstractManager->HandleRequest(_Request);
	}
};

void Test01()
{
	CAbstractManager* pcBOSS = new CBOSS(nullptr);
	CAbstractManager* pcCEO = new CCEO(pcBOSS);
	CAbstractManager* pcManager = new CManager(pcCEO);
	CEmployee cEmployee;

	cout << "提交相应请求给直属领导\n";
	cEmployee.SubmitRequest(pcManager, REQUEST::ASKFORLEAVE);
	cEmployee.SubmitRequest(pcManager, REQUEST::RAISESALARY);
	cEmployee.SubmitRequest(pcManager, REQUEST::RESIGN);

	cout << "\n提交相应请求给CEO\n";
	cEmployee.SubmitRequest(pcCEO, REQUEST::ASKFORLEAVE);
	cEmployee.SubmitRequest(pcCEO, REQUEST::RAISESALARY);
	cEmployee.SubmitRequest(pcCEO, REQUEST::RESIGN);

	cout << "\n提交相应请求给BOSS\n";
	cEmployee.SubmitRequest(pcBOSS, REQUEST::ASKFORLEAVE);
	cEmployee.SubmitRequest(pcBOSS, REQUEST::RAISESALARY);
	cEmployee.SubmitRequest(pcBOSS, REQUEST::RESIGN);

	delete pcManager;
	delete pcCEO;
	delete pcBOSS;
	pcManager = nullptr;
	pcCEO = nullptr;
	pcBOSS = nullptr;
}

int main()
{
	Test01();
	return 0;
}
