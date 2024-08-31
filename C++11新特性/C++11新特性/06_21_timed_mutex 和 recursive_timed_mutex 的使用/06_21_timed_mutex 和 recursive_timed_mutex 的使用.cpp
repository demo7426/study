/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_21_timed_mutex 和 recursive_timed_mutex 的使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.06
描  述: timed_mutex 在一个线程内部可以超时等待加锁，若加锁失败则返回false，成功返回true; recursive_timed_mutex 是timed_mutex和recursive_mutex的结合体;
备  注:
修改记录:

  1.  日期: 2024.07.06
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
			if (m_cCountMutex.try_lock_for(std::chrono::milliseconds(1)))
			{
				std::cout << "Increment lock success." << '\n';
				++m_nCount;
				std::cout << "++Increment: " << m_nCount << '\n';
				m_cCountMutex.unlock();
			}
			else
			{
				std::cout << "Increment lock failed." << '\n';
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
			m_cCountMutex.lock();
			--m_nCount;
			std::cout << "--Decrement: " << m_nCount << '\n';
			m_cCountMutex.unlock();

			std::this_thread::yield();
		}

		return EXIT_SUCCESS;
	}

private:
	std::timed_mutex m_cCountMutex;									//互斥量，用于保护 m_nCount 临界资源
	unsigned int m_nCount = 100;									//总数
};

int Test01()
{
	CBase cBase;

	std::thread cTh01(&CBase::Increment, &cBase, 100);
	std::thread cTh02(&CBase::Decrement, &cBase, 100);

	cTh01.join();
	cTh02.join();

	return EXIT_SUCCESS;
}

int main()
{
	Test01();

	return EXIT_SUCCESS;
}


