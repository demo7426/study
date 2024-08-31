/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_19_死锁和 lock_guard 类的使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.06.29
描  述: 使用 lock_guard 类保护临界资源
备  注:
修改记录:

  1.  日期: 2024.06.29
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include <iostream>
#include <thread>
#include <mutex>

class CBase
{
public:
	CBase() = default;
	~CBase() = default;

	/// <summary>
	/// 自增函数
	/// </summary>
	/// <param name="_Num">自增次数</param>
	/// <returns></returns>
	int Increment(const unsigned int& _Num)
	{
		for (size_t i = 0; i < _Num; i++)
		{
			{
				std::lock_guard<std::mutex> cLock_Guard(m_cCountMutex);
				++m_nCount;
				std::cout << "++Increment: " << m_nCount << '\n';
			}

			std::this_thread::sleep_for(std::chrono::nanoseconds(1));
		}

		return EXIT_SUCCESS;
	}

	/// <summary>
	/// 自减函数
	/// </summary>
	/// <param name="_Num">自减次数</param>
	/// <returns></returns>
	int Decrement(const unsigned int& _Num)
	{
		for (size_t i = 0; i < _Num; i++)
		{
			{
				std::lock_guard<std::mutex> cLock_Guard(m_cCountMutex);
				--m_nCount;
				std::cout << "--Decrement: " << m_nCount << '\n';
			}

			std::this_thread::yield();
		}

		return EXIT_SUCCESS;
	}


private:
	std::mutex m_cCountMutex;									//互斥量，用于保护 m_nCount 临界资源
	unsigned int m_nCount = 100;								//总数
};

int Test01()
{
	CBase cBase;

	std::thread cTh01(&CBase::Increment, &cBase, 10);
	std::thread cTh02(&CBase::Decrement, &cBase, 10);

	cTh01.join();
	cTh02.join();

	return EXIT_SUCCESS;
}

int main()
{
	Test01();

	return EXIT_SUCCESS;
}

