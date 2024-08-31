/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_38_packaged_task 类的使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.13
描  述: 使用packaged_task类封装线程回调函数，在线程中使用return返回值，使用future对象接收返回值
备  注:	每一个packaged_task对象内部都维护者一个future对象
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
	CBase cBase;

	//1、普通函数
	std::packaged_task<int(std::string)> cPackaged_Task01(Printf);
	std::thread cTh01(std::ref(cPackaged_Task01), "普通函数调用");

	cTh01.join();
	std::future<int> cFuture01 = cPackaged_Task01.get_future();
	std::cout << "普通函数的调用返回值为：" << cFuture01.get() <<  '\n' << std::endl;

	//2、匿名函数
	std::packaged_task<int(std::string)> cPackaged_Task02([](std::string _Arg) ->int {
		std::cout << "匿名函数调用：" << _Arg << std::endl;
		return EXIT_SUCCESS;
		});

	std::thread cTh02(std::ref(cPackaged_Task02), "123");
	cTh02.join();
	std::future<int> cFuture02 = cPackaged_Task02.get_future();
	std::cout << "匿名函数的调用返回值为：" << cFuture02.get() << '\n' << std::endl;

	//3、仿函数
	std::packaged_task<int(std::string)> cPackaged_Task03(cBase);

	std::thread cTh03(std::ref(cPackaged_Task03), "456");
	cTh03.join();
	std::future<int> cFuture03 = cPackaged_Task03.get_future();
	std::cout << "仿函数的调用返回值为：" << cFuture03.get() << '\n' << std::endl;

	//4、将类对象进行转换得到的函数指针
	std::packaged_task<int(std::string, int)> cPackaged_Task04(cBase);

	std::thread cTh04(std::ref(cPackaged_Task04), "456", 10);
	cTh04.join();
	std::future<int> cFuture04 = cPackaged_Task04.get_future();
	std::cout << "仿函数的调用返回值为：" << cFuture04.get() << '\n' << std::endl;
	
	//5、静态函数
	std::packaged_task<int(std::string, int)> cPackaged_Task05(&CBase::ShowMsg);

	std::thread cTh05(std::ref(cPackaged_Task05), "456", 10);
	cTh05.join();
	std::future<int> cFuture05 = cPackaged_Task05.get_future();
	std::cout << "静态函数的调用返回值为：" << cFuture05.get() << '\n' << std::endl;
	
	//6、非静态函数
	auto it = std::bind(&CBase::AddNum, &cBase, std::placeholders::_1, std::placeholders::_2);

	std::packaged_task<int(int, int)> cPackaged_Task06(it);
	 
	std::thread cTh06(std::ref(cPackaged_Task06), 10, 20);
	cTh06.join();
	std::future<int> cFuture06 = cPackaged_Task06.get_future();
	std::cout << "非静态函数的调用返回值为：" << cFuture06.get() << '\n' << std::endl;

	return EXIT_SUCCESS;
}

int main()
{
	Test01();

	return EXIT_SUCCESS;
}
