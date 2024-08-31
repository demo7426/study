//文件描述：
//      测试initializer_list模板类，轻量级容器类型
//作者：钱锐
//时间：2024/03/06
//修改记录：
//      2024/03/06     新建

#include <iostream>

template<class T>
int PrintfInitializer_list(const std::initializer_list<T>& _Arg)
{
	for (auto it = _Arg.begin(); it != _Arg.end(); ++it)
	{
		std::cout << *it << " ";
	}

	std::cout << std::endl;
	
	return 0;
}

int main(int argc, char argv[], char envp[])
{
	PrintfInitializer_list<int>({ 1,2,3,4,5,6 });

	return 0;
}
