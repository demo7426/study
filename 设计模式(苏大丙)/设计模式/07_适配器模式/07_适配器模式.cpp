//文件描述：
//      实现一个适配器模式（处理不同的数据相互转换情况）
//作者：钱锐
//时间：2024/1/23
//修改记录：
//      2024/1/23     新建

#include <iostream>

using namespace std;

class CAbstractForeigner
{
public:
    virtual~CAbstractForeigner() {};

    //承认错误
    virtual string ConfessMistake() = 0;

    //打印接收到的结果
    void PrintfRecvResult(string _Context)
    {
        cout << _Context << endl;
    }
private:

};

class CAmerican : public CAbstractForeigner
{
public:
    ~CAmerican() {};

    string ConfessMistake() override
    {
        return "美国人：我承认自己猎杀过熊猫的错误";
    }
        
private:

};

class CFrechman : public CAbstractForeigner
{
public:
    ~CFrechman() {};

    string ConfessMistake() override
    {
        return "法国人：我承认自己猎杀、购买熊猫的错误";
    }


private:

};

class CPanda
{
public:
    ~CPanda() {}
    
    string SendMsg()
    {
        return "你们是永远不能得到宽恕和原谅的";
    }
    
    //打印接收到的结果
    void PrintfRecvResult(string _Context)
    {
        cout << _Context << endl;
    }

private:

};


class CAbstractTranslator
{
public:
    CAbstractTranslator(CAbstractForeigner* _pAbstractForeigner, CPanda* _pPanda) : m_pcAbstractForeigner(_pAbstractForeigner), m_pcPanda(_pPanda)
    {}

    virtual ~CAbstractTranslator() {}
    virtual void TranslateToMan() = 0;         //翻译给人
    virtual void TranslateToPanda() = 0;       //翻译给熊猫

protected:
    CAbstractForeigner* m_pcAbstractForeigner = nullptr;
    CPanda* m_pcPanda = nullptr;
};

class CAmericanTanlator : public CAbstractTranslator
{
public:
    using CAbstractTranslator::CAbstractTranslator;             //继承构造函数

    ~CAmericanTanlator() = default;
    void TranslateToMan() override
    {
        string strContext = m_pcPanda->SendMsg();

        //数据转换
        
        m_pcAbstractForeigner->PrintfRecvResult("熊猫说：美国人" + strContext);
    }

    void TranslateToPanda()
    {
        string strContext = m_pcAbstractForeigner->ConfessMistake();

        //数据转换

        m_pcPanda->PrintfRecvResult(strContext);
    }

private:

};

class CFrechmanTanlator : public CAbstractTranslator
{
public:
    using CAbstractTranslator::CAbstractTranslator;             //继承构造函数

    ~CFrechmanTanlator() = default;
    void TranslateToMan() override
    {
        string strContext = m_pcPanda->SendMsg();

        //数据转换
        
        m_pcAbstractForeigner->PrintfRecvResult("熊猫说：法国人" + strContext);
    }

    void TranslateToPanda()
    {
        string strContext = m_pcAbstractForeigner->ConfessMistake();

        //数据转换

        m_pcPanda->PrintfRecvResult(strContext);
    }

private:

};

void Test01()
{
    CAbstractForeigner* pcAbstractForeigner = new CAmerican;
    CPanda* pcPanda = new CPanda;
    CAbstractTranslator* pcAbstractTranslator = new CAmericanTanlator(pcAbstractForeigner, pcPanda);

    pcAbstractTranslator->TranslateToPanda();
    pcAbstractTranslator->TranslateToMan();

    delete pcAbstractTranslator;
    delete pcPanda;
    delete pcAbstractForeigner;
}

void Test02()
{
    CAbstractForeigner* pcAbstractForeigner = new CFrechman;
    CPanda* pcPanda = new CPanda;
    CAbstractTranslator* pcAbstractTranslator = new CFrechmanTanlator(pcAbstractForeigner, pcPanda);

    pcAbstractTranslator->TranslateToPanda();
    pcAbstractTranslator->TranslateToMan();

    delete pcAbstractTranslator;
    delete pcPanda;
    delete pcAbstractForeigner;
}

int main()
{
    Test01();
    cout << "\n";
    Test02();

    return 0;
}