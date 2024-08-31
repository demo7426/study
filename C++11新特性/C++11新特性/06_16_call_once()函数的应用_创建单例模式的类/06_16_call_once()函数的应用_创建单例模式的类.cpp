/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_15_call_once()函数的使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.06.13
描  述: 使用 call_once 实现单例设计模式
备  注:
修改记录:

  1.  日期: 2024.06.13
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include <iostream>
#include <mutex>
#include <thread>

std::once_flag g_tOnceFlag;

class CStudent
{
public:
	CStudent(const CStudent&) = delete;
	CStudent(const CStudent&&) = delete;
	CStudent& operator=(CStudent&) = delete;
	CStudent& operator=(CStudent&&) = delete;
	~CStudent();

	static CStudent* GetInstance()
	{
		std::call_once(g_tOnceFlag, [&]()
			{
				if (m_pcStudent == nullptr)
				{
					std::cout << "call_once 被调用了..." << '\n';
					m_pcStudent = new CStudent();
				}
			});

		return m_pcStudent;
	}

	int SetName(std::string _Name)
	{
		this->m_strName = _Name;
		return EXIT_SUCCESS;
	}

	std::string GetName()
	{
		return this->m_strName;
	}

private:
	static CStudent* m_pcStudent;
	std::string m_strName = std::string();

private:
	CStudent() = default;
};

CStudent* CStudent::m_pcStudent = nullptr;

CStudent::~CStudent()
{
	if (m_pcStudent != nullptr)
	{
		delete m_pcStudent;
		m_pcStudent = nullptr;
	}
}

void CalledFunc(std::string _Name)
{
	CStudent* pcStudent = CStudent::GetInstance();
	
	pcStudent->SetName(_Name);

	std::cout << "CalledFunc: " << pcStudent->GetName() << '\n';
}

int Test01()
{
	std::thread cTh01(CalledFunc, "Cristiano01");
	std::thread cTh02(CalledFunc, "Cristiano02");
	std::thread cTh03(CalledFunc, "Cristiano03");

	cTh01.join();
	cTh02.join();
	cTh03.join();

	return EXIT_SUCCESS;
}


int main()
{
	Test01();

	return EXIT_SUCCESS;
}


