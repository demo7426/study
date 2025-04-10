/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cc
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.11
描  述: 实现一个基于protoc的简单序列化、反序列化的程序
备  注:	
修改记录:

  1.  日期: 2025.04.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <iostream>

#include "Person.pb.h"

int main(void)
{
    Person cPerson_In;
    cPerson_In.set_id(10);
    cPerson_In.set_name("lu_fei");
    cPerson_In.set_sex("man");
    cPerson_In.set_age(18);

    //序列化对象，最终得到一个字符串
    std::string strOutput;
    cPerson_In.SerializeToString(&strOutput);

    //反序列化数据
    Person cPerson_Out;
    cPerson_Out.ParseFromString(strOutput);

    std::cout << "id = " << cPerson_Out.id() << ", name = " << cPerson_Out.name() << ", sex = " << cPerson_Out.sex() << ", age = " << cPerson_Out.age() << std::endl;

    return 0;
}

