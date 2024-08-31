//文件描述：
//      测试抛出、禁止异常函数
//作者：钱锐
//时间：2024/03/01
//修改记录：
//      2024/03/01     新建

#include <iostream>

struct _PERSON_INFO
{
	_PERSON_INFO(int _Age) : Age(_Age) {}
	int Age;
};

void Test01()
{
	try
	{
		throw 1;
	}
	catch (const int& e)
	{
		std::cout << "Test01 抛出异常：" << e << std::endl;
	}
}

void Test02() throw(std::exception*, _PERSON_INFO*) //throw(参数1, 参数2, ......)允许该函数向外抛出哪些异常
{
	try
	{
		throw new std::exception("1111");
	}
	catch (const std::exception* e)
	{
		std::cout << "Test02 抛出异常：" << e->what() << std::endl;
	}

	try
	{
		throw new _PERSON_INFO(18);
	}
	catch (const _PERSON_INFO* e)
	{
		std::cout << "Test02 抛出异常：" << e->Age << std::endl;
	}
}

void Test03() noexcept(true) //不允许该函数向外抛出异常
{
	throw 1;
}

int main()
{
	Test01();
	Test02();

	try
	{
		Test03();
	}
	catch (const int& e)
	{
		std::cout << "Test03 抛出异常：" << e << std::endl;
	}

	return 0;
}
