//文件描述：
//      独占的智能指针unique_ptr的初始化及使用
//作者：钱锐
//时间：2024/03/17
//修改记录：
//      2024/03/17    新建
#include <iostream>
#include <memory>

class CTest
{
public:
	CTest() = default;
	CTest(int _Num) : m_nNum(_Num) {}
	CTest(std::string _ClassName) : m_strClassName(_ClassName) {}

	int SetNum(int _Num)
	{
		m_nNum = _Num;
		return EXIT_SUCCESS;
	}

	void PrintfNum()
	{
		std::cout << "Num = " << m_nNum << std::endl;
	}

private:
	int m_nNum = 0;
	std::string m_strClassName = std::string();
};

void Test01()
{
	//通过构造函数初始化
	std::unique_ptr<int> pnValue(new int(10));

	//通过移动构造函数初始化
	std::unique_ptr<int> pnValue02(std::move(pnValue));

	//通过reset初始化
	pnValue02.reset(new int(11));

	//使用
	*pnValue02 = 13;
}

int main()
{
	Test01();

	return 0;
}

