//文件描述：
//      使用weak_ptr解决shared_ptr管理的内存被重复析构的问题
//			1、不能使用同一个原始地址初始化多个共享智能指针
//			2、函数不能返回管理了this的共享智能指针对象
//			3、共享智能指针不能够循环引用（会导致引用计数无法为0，导致不释放内存；解决方法使用弱引用智能指针代替，解开循环。）
//作者：钱锐
//时间：2024/03/17
//修改记录：
//      2024/03/17    新建

#include <iostream>
#include <memory>
#include <functional>

class CTest : public std::enable_shared_from_this<CTest>
{
public:
	~CTest()
	{
		std::cout << "~CTest被调用了" << std::endl;
	}

	std::shared_ptr<CTest> GetShared_Ptr()
	{
		return this->shared_from_this();			/*enable_shared_from_this<CTest>类里面有一个弱引用智能指针，
														调用了弱引用智能指针的lock()方法，返回了一个共享指针对象*/
		//return std::shared_ptr<CTest>(this);
	}

private:
};

void Test01()
{
	int* pnValue01 = new int(10);

	//不能使用同一个原始地址初始化多个共享智能指针
	std::shared_ptr<int> pnValue02(pnValue01);
	//std::shared_ptr<int> pnValue03(pnValue01);

	//函数不能返回管理了this的共享智能指针对象
	std::shared_ptr<CTest> pcTest01(new CTest);
	std::shared_ptr<CTest> pcTest02 = pcTest01->GetShared_Ptr();

}

int main()
{
	Test01();

	return 0;
}

