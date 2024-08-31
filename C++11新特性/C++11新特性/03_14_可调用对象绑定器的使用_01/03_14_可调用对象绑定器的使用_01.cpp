//文件描述：
//      可调用对象绑定器的作为参数进行传递
//作者：钱锐
//时间：2024/03/07
//修改记录：
//      2024/03/07     新建

#include <iostream>
#include <functional>


int Printf_Add(int _X, int _Y)
{
	std::cout << _X << " + " << _Y << " = " << _X + _Y << std::endl;

	return 0;
}

void MyPrintf(int _X, int _Y, std::function<int(int, int)> _Func)
{
	if (_X % 2 == 0)
	{
		_Func(_X, _Y);		//包装器函数参数最高优先级为绑定器指定参数
	}
}


int main()
{
	for (int i = 0; i < 10; i++)
	{
		auto obj = std::bind(Printf_Add, i + 100, i + 100);
		MyPrintf(i, i, obj);
	}

	return 0;
}
