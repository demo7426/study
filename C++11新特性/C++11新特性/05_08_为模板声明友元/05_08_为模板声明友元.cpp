/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	05_08_为模板声明友元.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.05.04
描  述: 实现友元类、友元函数
备  注:
        friend 模板友元在 C++11 标准后去掉class关键字后才能支持

修改记录:

  1.  日期: 2024.05.04
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include <iostream>

/// <summary>
/// 矩形类
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class CRectangle
{
    friend T;

public:
    CRectangle() = delete;
    CRectangle(int _Length, int _Width) noexcept : m_nLength(_Length), m_nWidth(_Width) 
    {}

	~CRectangle() = default;

private:
    int m_nLength = 0;
    int m_nWidth = 0;
};

/// <summary>
/// 圆形类
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class CCircle
{
    friend T;

public: 
    CCircle(int _Radius) noexcept : m_nRadius(_Radius){ }
    ~CCircle() = default;

private:
    CCircle() = default;

    int m_nRadius = 0;
};

class CVertify
{
public:
    CVertify() = delete;
    CVertify(const CVertify&) = delete;
    CVertify(CVertify&&) = delete;

    CVertify(const int& _Length, const int& _Width, const CRectangle<CVertify>& _Vertify)
    {
        if (_Length < _Vertify.m_nLength && _Width < _Vertify.m_nWidth)
            std::cout << "长宽满足条件" << std::endl;
        else
            std::cout << "长宽不满足条件" << std::endl;
    }


    CVertify(const int& _Radius, const CCircle<CVertify>& _Vertify)
    {
        if (_Radius < _Vertify.m_nRadius)
            std::cout << "半径满足条件" << std::endl;
        else
            std::cout << "半径不满足条件" << std::endl;
    }
};


void Test01() throw ()
{
    CRectangle<CVertify> cRecTangle(100, 200);
    CCircle<CVertify> cCircle(50);

    CVertify(50, 100, cRecTangle);
    CVertify(80, cCircle);
}

int main()
{
    Test01();

    return EXIT_SUCCESS;
}
