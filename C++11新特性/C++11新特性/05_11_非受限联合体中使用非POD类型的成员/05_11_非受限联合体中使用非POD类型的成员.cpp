/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	05_11_非受限联合体中使用非POD类型的成员.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.05.08
描  述: 在C++98的基础上，C++11新增支持联合体内部元素为非POD类型、静态成员、静态函数，仍暂不支持左值引用
备  注:
        如果使用联合体内部元素有非POD类型，需要自己重写构造函数，语法才能支持

修改记录:

  1.  日期: 2024.05.08
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

    inline void SetName(std::string _Name) throw()
    {
        m_strName = _Name;
    }

private:
    std::string m_strName;
};


union Test
{
    Test()
    {
        //定位最大的数据空间
        new (&Name)std::string;         //定位防止new操作符，使用已存在的&Name空间，而不是去申请新的空间
    }
    ~Test(){}
    /*非POD类型*/

    CTeacher Teacher;
    std::string Name;

    int Value01;
};

void Test01()
{
    Test uTest;
    
    uTest.Name = "Xi'an";
    uTest.Teacher.SetName("Chengdu");

    std::cout << uTest.Name << std::endl;
}

int main()
{
    Test01();

    return EXIT_SUCCESS;
}


