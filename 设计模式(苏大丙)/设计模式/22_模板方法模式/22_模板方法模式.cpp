//文件描述：
//      实现一个模板方法模式（实质就是子类重写父类）
//作者：钱锐
//时间：2024/2/28
//修改记录：
//      2024/2/28     新建

#include <iostream>

class CPerson
{
public:
    virtual void PrintfName() = 0;
    virtual void PrintfAbility() = 0;
    virtual void PrintfSex()
    {
        std::cout << "man" << std::endl;
    }
};

class CBob : public CPerson
{
public:
    void PrintfName() override
    {
        std::cout << "Bob" << std::endl;
    }

    void PrintfAbility() override
    {
        std::cout << "teach student." << std::endl;
    }
};

class CAgela : public CPerson
{
public:
    void PrintfName() override
    {
        std::cout << "Agela" << std::endl;
    }

    void PrintfAbility() override
    {
        std::cout << "nurse." << std::endl;
    }

    void PrintfSex() override
    {
        std::cout << "woman" << std::endl;
    }
};


int main()
{
    CPerson* pcBob = new CBob;
    pcBob->PrintfName();
    pcBob->PrintfSex();
    pcBob->PrintfAbility();
    delete pcBob;

    std::cout << "======================" << std::endl;
    pcBob = new CAgela;
    pcBob->PrintfName();
    pcBob->PrintfSex();
    pcBob->PrintfAbility();
    delete pcBob;



    return 0;
}

