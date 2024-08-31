//文件描述：
//      测试静态断言 static_assert 函数
//作者：钱锐
//时间：2024/03/01
//修改记录：
//      2024/03/01     新建

#include <iostream>

int main()
{
    //第一个参数为静态常量表达式
    static_assert(sizeof(long) == 8, "当前系统并非为Linux 64 位操作系统");
    return 0;
}


