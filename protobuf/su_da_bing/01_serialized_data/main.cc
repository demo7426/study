/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cc
作  者:	钱锐      版本: V0.1.1     新建日期: 2025.04.11
描  述: 实现一个基于protoc的简单序列化、反序列化的程序
备  注:	终端使用 protoc -I./ Person.proto --cpp_out=./ 生成c++文件
修改记录:

  1.  日期: 2025.04.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

  2.  日期: 2025.04.11
      作者: 钱锐
      内容:
          1) 新增protobuf使用嵌套符合数据类型、枚举、导入其他proto文件；
          1) 新增protobuf包使用，编译后即C++中的命名空间；
      版本:V0.1.1

*************************************************/

#include <iostream>

#include "Person.pb.h"

int main(void)
{
    NameSpaca_Person::CPerson cPerson_In;
    cPerson_In.set_id(10);

    //设置数组字段值
    cPerson_In.add_name();
    cPerson_In.set_name(0, "zhao_yun");
    cPerson_In.add_name();
    cPerson_In.set_name(1, "zhang_fei");

    cPerson_In.set_sex("man");
    cPerson_In.set_age(18);

    //设置嵌套字段值
    cPerson_In.mutable_address()->set_addr_name("四川省成都市武侯区芳草街道");
    cPerson_In.mutable_address()->set_addr_id(1001);

    //设置枚举字段值
    cPerson_In.set_color(NameSpaca_Person::COLOR::BLACK);    
    
    //序列化对象，最终得到一个字符串
    std::string strOutput;
    cPerson_In.SerializeToString(&strOutput);

    //反序列化数据
    NameSpaca_Person::CPerson cPerson_Out;
    cPerson_Out.ParseFromString(strOutput);

    std::cout << "id = " << cPerson_Out.id() << ", sex = " << cPerson_Out.sex() << ", age = " << cPerson_Out.age() << std::endl;

    for (int i = 0; i < cPerson_Out.name_size(); i++)
    {
        printf("name[%d] = %s\n", i, cPerson_Out.name(i).data());
    }
    
    std::cout << "addr_name = " << cPerson_Out.address().addr_name() << ", addr_id = " << cPerson_Out.address().addr_id() << std::endl;
    std::cout << "color = " << cPerson_Out.color() << std::endl;
    
    return 0;
}

