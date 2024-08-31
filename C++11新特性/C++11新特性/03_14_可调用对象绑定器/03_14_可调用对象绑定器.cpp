//文件描述：
//      可调用对象绑定器的简单使用
//作者：钱锐
//时间：2024/03/07
//修改记录：
//      2024/03/07     新建

#include <iostream>
#include <functional>

int MyPrintf(int _Num, std::string _Msg)
{
    std::cout << "Printf: " << "_Num = " << _Num << "\t_Msg = " << _Msg << std::endl;
    return 0;
}

void Test01()
{
    std::bind(MyPrintf, 10, "第一条日志")();

    std::bind(MyPrintf, std::placeholders::_1, std::placeholders::_2)(11, "第二条日志");

    std::bind(MyPrintf, 13, std::placeholders::_2)(12, "第三条日志");

    std::bind(MyPrintf, std::placeholders::_2, std::placeholders::_1)("第四条日志", 14);
}

int main()
{
    Test01();

    return 0;
}


