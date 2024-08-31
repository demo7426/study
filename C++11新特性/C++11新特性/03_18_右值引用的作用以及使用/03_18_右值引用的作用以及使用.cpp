//文件描述：
//      右值引用的使用（类移动构造语句触发条件）
//          1.想要调用移动构造语句需要显示的指出，C++20 标准编译器不会默认转换
//          2.只要右值引用被传递（被使用）了就会变成左值引用
//作者：钱锐
//时间：2024/03/08
//修改记录：
//      2024/03/08    新建

#include <iostream>

class CTest
{
public:
    CTest() noexcept : m_pnNum(new int(0))
    {
        std::cout << "无参构造函数" << std::endl;
    }

    CTest(const CTest& _Test) noexcept : m_pnNum(new int(*(_Test.m_pnNum)))
    {
        std::cout << "拷贝构造函数" << std::endl;
    }

    CTest(CTest&& _Test) noexcept : m_pnNum(_Test.m_pnNum)
    {
        _Test.m_pnNum = nullptr;
        std::cout << "移动构造函数" << std::endl;
    }

public:
    int* m_pnNum = nullptr;
};

CTest GetTestObj()
{
    CTest cTest;
    std::cout <<  "GetTestObj: Num ptr = " << cTest.m_pnNum << std::endl;

    return std::move(cTest);
    //return CTest();
}

void Test01()
{
    CTest cTest = GetTestObj();
    std::cout << "Test01: Num ptr = " << cTest.m_pnNum << std::endl;
}

int main()
{
    Test01();

    return 0;
}


