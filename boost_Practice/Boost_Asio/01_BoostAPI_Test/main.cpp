/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.15
描  述: 对boost的部分API进行测试，使用 boost::lexical_cast 转换数据
备  注:	
修改记录:

  1.  日期: 2025.04.15
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <iostream>
#include "boost/lexical_cast.hpp"

int main()
{
    float fWeight = 0;      //体重
    std::string strData = "A 10% increase raise ";

    std::cout << "Enter your weight:";
    std::cin >> fWeight;

    strData = strData + boost::lexical_cast<std::string>(fWeight) + " to ";

    fWeight *= 1.1;
    strData = strData + boost::lexical_cast<std::string>(fWeight) + ".";

    std::cout << strData << std::endl;

    return 0;
}

