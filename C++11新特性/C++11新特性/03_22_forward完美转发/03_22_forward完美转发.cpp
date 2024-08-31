/*************************************************
Copyright (C), 2009-2012    , Leetro Automation Co., Ltd.
文件名:	03_22_forward完美转发.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.03.20
描  述: C++11新特性forward完美转发测试
备  注:	std::forward<T>t 当T类型为左值引用时，转换出来的依然为左值引用；反之，为右值引用

修改记录:

  1.  日期: 2024.03.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/
#include <iostream>

template<typename T>
void MyPrintf(T&& _Arg)
{
    std::cout << "r_value " << _Arg << std::endl;
}

template<typename T>
void MyPrintf(T& _Arg)
{
    std::cout << "l_value " << _Arg << std::endl;
}

template<typename T>
int Test01(T&& _Arg)
{
    MyPrintf(_Arg);
    MyPrintf(std::move(_Arg));
    MyPrintf(std::forward<T>(_Arg));

    return EXIT_SUCCESS;
}


int main()
{
    int nNum = 999;

    Test01(100);                            //左 右 右
    Test01(nNum);                           //左 右 左
    Test01(std::forward<int>(nNum));        //左 右 右
    Test01(std::forward<int&>(nNum));       //左 右 左
    Test01(std::forward<int&&>(nNum));      //左 右 右

    return EXIT_SUCCESS;
}

