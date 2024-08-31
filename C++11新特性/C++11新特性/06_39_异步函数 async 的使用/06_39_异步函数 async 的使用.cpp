/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_39_异步函数 async 的使用 类的使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.13
描  述: 使用async类封装线程回调函数，在线程中使用return返回值，使用future对象接收返回值
备  注:	每一个async对象内部都维护者一个future对象；
		async函数有两种调用策略：
			1、std::launch::async表示立即创建线程调用回调函数；
			2、std::launch::deferred表示知道调用了future类的get()或wait()时才执行任务（这种方式不会创建新的线程）；
修改记录:

  1.  日期: 2024.07.13
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include <iostream>
#include <future>
#include <thread>
#include <functional>
#include <chrono>

static int Printf(std::string _Arg)
{
	std::cout << "Printf " << _Arg << std::endl;

	return EXIT_SUCCESS;
}

static class CBase
{
private:
	using FuncType = int(*)(std::string, int);

public:
	CBase() = default;
	~CBase() = default;

	/// <summary>
	/// 仿函数
	/// </summary>
	/// <param name="_Arg"></param>
	/// <returns></returns>
	int operator()(std::string _Arg)
	{
		std::cout << std::string("CBase 仿函数: " + _Arg) << std::endl;

		return EXIT_SUCCESS;
	}

	operator FuncType()
	{
		return this->ShowMsg;
	}

	/// <summary>
	/// 计算两数之和
	/// </summary>
	/// <param name="_Num"></param>
	/// <returns></returns>
	int AddNum(int _X, int _Y)
	{
		std::cout << "CBase AddNum函数: " << _X << " + " << _Y << " = " << _X + _Y << std::endl;

		return _X + _Y;
	}

	static int ShowMsg(std::string _Arg, int _Num)
	{
		std::cout << "CBase ShowMsg函数:\n";
		for (int i = 0; i < _Num; i++)
		{
			std::cout << _Arg << std::endl;
		}
		return EXIT_SUCCESS;
	}

private:

};

int Test01(void)
{
	std::cout << "主线程 id is " << std::this_thread::get_id() << std::endl;

	std::future<int> it = std::async([](int _Arg) {
		std::cout << "线程 id is " << std::this_thread::get_id() << ", " << _Arg << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return 120;
		}, 100);

	std::cout << "线程回调函数返回值为：" << it.get() << std::endl;

	return EXIT_SUCCESS;
}


int Test02(void)
{
	std::cout << "主线程 id is " << std::this_thread::get_id() << std::endl;

	std::future<int> it = std::async(std::launch::deferred, [](int _Arg) {
		std::cout << "线程 id is " << std::this_thread::get_id() << ", " << _Arg << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return 120;
		}, 100);

	std::this_thread::sleep_for(std::chrono::seconds(10));
	std::cout << "线程回调函数返回值为：" << it.get() << std::endl;

	return EXIT_SUCCESS;
}

int main()
{
	Test02();

	return EXIT_SUCCESS;
}
