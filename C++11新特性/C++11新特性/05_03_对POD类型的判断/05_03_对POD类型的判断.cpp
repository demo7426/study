/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	05_23_对POD类型的判断.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.04.23
描  述: 对POD类型的判断
备  注:	不同的编译器及环境对于POD的判定不同；推荐使用is_trivial、is_standard_layout判断是否为POD平凡或标准数据类型

修改记录:

  1.  日期: 2024.04.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include <iostream>

class CTeacher
{
public:
    int m_nAge = 46;
    //std::string m_nName = "";
};

class CTeacher02 : public CTeacher
{

};


int main(int argc, char* argv[], char envp[])
{
    std::cout << "CTeacher is " << std::is_trivial<CTeacher>::value << std::endl;                   //POD平凡数据类型
    std::cout << "CTeacher02 is " << std::is_standard_layout<CTeacher02>::value << std::endl;       //POD标准数据类型


    return 0;
}

