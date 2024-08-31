//文件描述：
//      编写4中不同的可调用对象
//          1.是一个函数指针
//          2.是一个具有operator()成员函数的类对象（仿函数）
//          3.是一个可以被转换为函数指针的类对象
//          4.是一个类成员函数指针或者类成员指针
//作者：钱锐
//时间：2024/03/06
//修改记录：
//      2024/03/06     新建

#include <iostream>

using FuncType01 = void(*)(int, std::string);

class CTest
{
public:
    void operator()(std::string _Arg)
    {
        std::cout << _Arg << std::endl;
    }

    operator FuncType01()
    {
        return Printf;
    }

    void Hello(int _Num, std::string _Msg)
    {
        std::cout << "Hello:  " << "_Num = " << _Num << "\t_Msg = " << _Msg << std::endl;
    }

    static void Printf(int _Num, std::string _Msg)
    {
        std::cout << "Printf: " << "_Num = " << _Num << "\t_Msg = " << _Msg << std::endl;
    }
public:
    int m_nValue = 0;

private:
   
};

void Test01()
{
    CTest cTest;

    //一个具有operator()成员函数的类对象（仿函数）
    cTest("第一条日志;");

    //一个可以被转换为函数指针的类对象
    cTest(10, "第二条日志;");

    //一个类成员函数指针
    using FuncType02 = void(CTest::*)(int, std::string);
    FuncType02 Func02 = &CTest::Hello;
    (cTest.*Func02)(11, "第三条日志;");

    //一个类成员指针
    using FuncType03 = int(CTest::*);
    FuncType03 Func03 = &CTest::m_nValue;
    cTest.*Func03 = 20;
    std::cout << "cTest.m_nValue = " << cTest.m_nValue << std::endl;
}

int main()
{
    Test01();
    return 0;
}

