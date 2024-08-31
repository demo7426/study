/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	05_10_非受限联合体中静态成员的使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.05.04
描  述: 在C++98的基础上，C++11新增支持联合体内部元素为非POD类型、静态成员、静态函数，仍暂不支持左值引用
备  注:
        如果使用联合体内部元素有非POD类型，需要自己重写构造函数，语法才能支持

修改记录:

  1.  日期: 2024.05.04
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/


#include <iostream>

class CTeacher                      //非POD类型，因为其重写了无参构造函数
{
public:
	CTeacher() {}
	~CTeacher() = default;

private:

};


union Test
{
    /*非POD类型*/

    //CTeacher Teacher;
    //std::string Name;

    /*静态元素*/

    static int Count;               //单独的内存区域，Count 与 Value01内存不是一个区域
    static void Printf()
    {
        std::cout <<  "Count: " << Count << std::endl;
    }

    /*左值引用元素*/

    int Value01;
    //int& Value02 = Value01;       //暂不支持左值引用
};

int Test::Count = 0;

void Test01()
{
    Test uTest01;
    uTest01.Count = 100;

    std::cout << "1: " << uTest01.Count << std::endl;
    uTest01.Printf();

    Test uTest02;
    uTest02.Count = 200;

    std::cout << "\n2: " << uTest01.Count << std::endl;
    uTest02.Printf();
}

int main()
{
    Test01();

    return EXIT_SUCCESS;
}


