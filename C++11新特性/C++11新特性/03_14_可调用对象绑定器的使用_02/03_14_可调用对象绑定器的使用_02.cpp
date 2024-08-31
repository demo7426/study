//文件描述：
//      使用绑定器绑定类的方法和字段
//作者：钱锐
//时间：2024/03/07
//修改记录：
//      2024/03/07     新建

#include <iostream>
#include <functional>

class CTest
{
public:
    void PrintfMsg(int _Num, std::string _Msg)
    {
        std::cout << "_Num: " << _Num << " _Msg: " << _Msg << '\n';
    }

public:
    int m_nValue = 0;
};


int main()
{
    CTest cTest;

    //绑定类方法
    auto obj = std::bind(&CTest::PrintfMsg, &cTest, std::placeholders::_1, std::placeholders::_2);
    std::function<void(int, std::string)> func = obj;

    func(10, "第一条日志");

    //绑定类字段
    auto obj02 = std::bind(&CTest::m_nValue, &cTest);
    std::function<int& ()> func02 = obj02;
    func02() = 100;

    std::cout << cTest.m_nValue << std::endl;

    return 0;
}
