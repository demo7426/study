/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	05_07_友元及友元的改进.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.05.04
描  述: 实现友元类、友元函数
备  注:
        friend 友元声明不会受到public、protected、private修饰符的影响

修改记录:

  1.  日期: 2024.05.04
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include <iostream>

class CRose;

class CTom
{
public:
    CTom() = default;
    ~CTom() = default;

    friend CRose;                       //C++98的写法为：friend class CRose;
    friend void Test02() throw ();

private:
    std::string m_strName = "Tom";

    inline void PrintfName() const noexcept
    {
        std::cout << "My name is " << this->m_strName << std::endl;
    }
};

class CJack
{
private:
    using Honey = CRose;
    friend Honey;
    friend void Test02() throw ();

public:
    CJack() = default;
    ~CJack() = default;

protected:
    std::string m_strName = "Jack";

    inline void PrintfName() const noexcept
    {
        std::cout << "My name is " << this->m_strName << std::endl;
    }
};

class CRose
{
public:
    CRose() = default;
    ~CRose() = default;

public:
    inline void PrintfAllName() const noexcept
    {
        std::cout << m_cJom.m_strName << '\n' << m_cJack.m_strName << std::endl;
        m_cJom.PrintfName();
        m_cJack.PrintfName();
    }

private:
    CTom m_cJom;
    CJack m_cJack;
};

void Test01() throw ()
{
    CRose cRose;
    cRose.PrintfAllName();
}

void Test02() throw ()
{
    CTom cJom;
    CJack cJack;

    std::cout << '\n' << cJom.m_strName << '\n' << cJack.m_strName << std::endl;
    cJom.PrintfName();
    cJack.PrintfName();
}

int main()
{
    Test01();

    return EXIT_SUCCESS;
}
