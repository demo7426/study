//文件描述：
//      可调用对象包装器的简单使用
//作者：钱锐
//时间：2024/03/07
//修改记录：
//      2024/03/07     新建

#include <iostream>
#include <functional>

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

void MyPrintf(int _Num, std::string _Msg)
{
    std::cout << "Printf: " << "_Num = " << _Num << "\t_Msg = " << _Msg << std::endl;
}


void Test01()
{
    CTest cTest;
    std::function<void(int, std::string)> func01 = MyPrintf;
    func01(1, "第一条日志");

    func01 = CTest::Printf;
    func01(2, "第二条日志");

    func01 = cTest;
    func01(3, "第三条日志");
}

int main()
{
    Test01();
    return 0;
}


