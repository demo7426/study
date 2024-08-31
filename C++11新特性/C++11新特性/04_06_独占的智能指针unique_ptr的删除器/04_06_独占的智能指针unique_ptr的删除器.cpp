//文件描述：
//      独占的智能指针unique_ptr的删除器
//作者：钱锐
//时间：2024/03/17
//修改记录：
//      2024/03/17    新建
#include <iostream>
#include <memory>
#include <functional>

class CTest
{
public:
	CTest() = default;
	CTest(int _Num) : m_nNum(_Num) {}
	CTest(std::string _ClassName) : m_strClassName(_ClassName) {}
	~CTest()
	{
		std::cout << "~CTest被调用" << std::endl;
	}

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
	std::unique_ptr<CTest, std::function<void(CTest*)>> pcTest01(new CTest(), [=](CTest* _pArg) {
		delete _pArg;
		});

	std::unique_ptr<CTest, std::function<void(CTest*)>> pcTest02(new CTest[4], [=](CTest* _pArg) {
		delete[] _pArg;
		});

	std::unique_ptr<CTest[]> pcTest03(new CTest[4]);

	//该写法在C++11以后的版本才支持维护数组，11版本不支持，所以尽量自己指定删除器
	std::shared_ptr<CTest[]> pcTest04(new CTest[4]);
}

int main()
{
	Test01();

	return 0;
}

