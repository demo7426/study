//文件描述：
//      共享智能指针shared_ptr的初始化及使用
//作者：钱锐
//时间：2024/03/14
//修改记录：
//      2024/03/14    新建

#include <iostream>
#include <memory>

class CTest
{
public:
    CTest(int _Num) : m_nNum(_Num){}
    CTest(std::string _ClassName) : m_strClassName(_ClassName) {}

    int SetNum(int _Num) 
    {
        m_nNum = _Num;
        return EXIT_SUCCESS;
    }

    void PrintfNum()
    {
        std::cout << "Num = " << m_nNum << std::endl;
    }

private:
    int m_nNum = 0;
    std::string m_strClassName = std::string();
};

//测试函数
void Test01()
{
    //初始化shared_ptr

    //1、使用构造函数初始化
    std::shared_ptr<int> pValue01(new int(10));
    std::cout << "pValue01 引用计数为：" << pValue01.use_count() << std::endl;

    //2、使用拷贝构造函数初始化
    std::shared_ptr<int> pValue02(pValue01);                    //可以写为: std::shared_ptr<int> pValue02 = pValue01; 
    std::cout << "pValue02 引用计数为：" << pValue02.use_count() << std::endl;

    //3、使用移动构造函数初始化
    std::shared_ptr<int> pValue03 = std::move(pValue02);        //可以写为: std::shared_ptr<int> pValue02(std::move(pValue02)); 
    std::cout << "pValue03 引用计数为：" << pValue03.use_count() << std::endl;

    //4、使用make_shared可变参函数模板初始化
    std::shared_ptr<int> pValue04 = std::make_shared<int>(11);
    std::cout << "pValue04 引用计数为：" << pValue04.use_count() << std::endl;

    std::cout << "\n";
    
    pValue03.reset();               //将pValue03的引用计数减去1
    std::cout << "pValue01 引用计数为：" << pValue01.use_count() << std::endl;
    std::cout << "pValue03 引用计数为：" << pValue03.use_count() << std::endl;

    *pValue01 = 100;

    std::cout << "\n///////////////////////////////////\n";

    //1、使用构造函数初始化
    std::shared_ptr<CTest> pcTest01(new CTest(10));
    std::cout << "pcTest01 引用计数为：" << pcTest01.use_count() << std::endl;

    //2、使用拷贝构造函数初始化
    std::shared_ptr<CTest> pcTest02(pcTest01);
    std::cout << "pcTest02 引用计数为：" << pcTest02.use_count() << std::endl;

    //3、使用移动构造函数初始化
    std::shared_ptr<CTest> pcTest03(std::move(pcTest02));
    std::cout << "pcTest03 引用计数为：" << pcTest03.use_count() << std::endl;

    //4、使用make_shared可变参函数模板初始化
    std::shared_ptr<CTest> pcTest04 = std::make_shared<CTest>(999);
    std::cout << "pcTest04 引用计数为：" << pcTest04.use_count() << std::endl;

    pcTest03.reset();               //将pValue03的引用计数减去1
    std::cout << "pcTest01 引用计数为：" << pcTest01.use_count() << std::endl;
    std::cout << "pcTest03 引用计数为：" << pcTest03.use_count() << std::endl;

    pcTest01->SetNum(9);
    pcTest01->PrintfNum();
}


int main()
{
    Test01();
    return 0;
}

