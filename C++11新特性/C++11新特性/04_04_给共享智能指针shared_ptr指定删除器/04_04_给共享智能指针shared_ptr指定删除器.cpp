//文件描述：
//      给共享智能指针shared_ptr指定删除器
//			注意当只能指针申请的空间为数组类型的空间时，必须指定删除器，以为编译器默认释放单个指针，而非delete[] 释放整个数组
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
	//自定义释放内存空间
	std::shared_ptr<CTest> pcTest(new CTest(10), [](CTest* _pTest) {
		delete _pTest;
		std::cout << "释放申请的 pcTest 内存" << std::endl;
		});

	std::shared_ptr<CTest> pcTests(new CTest[6], [](CTest* _pTest) {
		delete[] _pTest;
		std::cout << "释放申请的 pcTests 内存" << std::endl;
		});

	//使用默认释放模板函数
	std::shared_ptr<int> pnValues(new int[6], std::default_delete<int[]>());
}

int main()
{
	Test01();

	return 0;
}
