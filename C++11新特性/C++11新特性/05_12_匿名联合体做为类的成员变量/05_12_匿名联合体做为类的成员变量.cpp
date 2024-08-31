/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	05_12_匿名联合体做为类的成员变量.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.05.12
描  述: 将匿名联合体放入类中，类可以直接进行访问其字段
备  注:
        类中使用匿名联合体数据类型，可以有效的利用资源，可以在类内部直接访问联合体内部数据

修改记录:

  1.  日期: 2024.05.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include <iostream>

/// <summary>
/// 外来人员
/// </summary>
typedef struct _ALIEN_INFO
{ 
    struct _ALIEN_INFO(std::string _Domicile, std::string _TelNum) : Domicile(_Domicile), TelNum(_TelNum){}

    std::string Domicile;                   //户籍地
    std::string TelNum;                     //移动电话号码
}ALIEN_INFO, *PALIEN_INFO;

class CPerson
{
private:
    enum class PERSONTYPE : char
    {
        STUDENT = 1,                        //学生人员       
        LOCALPERSON,                        //本地非学生的人员
        ALIEN                               //外来人员
    };
public:
    CPerson() = delete;
    CPerson(int _SudentId) noexcept  : SudentId(_SudentId), m_ePersonType(PERSONTYPE::STUDENT) {}
    CPerson(std::string _IdCard) noexcept : IdCard(_IdCard), m_ePersonType(PERSONTYPE::LOCALPERSON) {}
    CPerson(std::string _Domicile, std::string _TelNum) noexcept : tAlien_Info(_Domicile, _TelNum), m_ePersonType(PERSONTYPE::ALIEN) {}
    ~CPerson() {};


    //向控制台输出当前类所有字段信息
    void Printf()
    {
        switch (m_ePersonType)
        {
        case CPerson::PERSONTYPE::STUDENT:
            std::cout << "Student: SudentId = " << SudentId << std::endl;
            break;
        case CPerson::PERSONTYPE::LOCALPERSON:
            std::cout << "Local person: IdCard = " << IdCard << std::endl;
            break;
        case CPerson::PERSONTYPE::ALIEN:
            std::cout << "Alien: Domicile = " << tAlien_Info.Domicile << ", TelNum = "<< tAlien_Info.TelNum << std::endl;
            break;
        default:
            break;
        }
    }

private:
    PERSONTYPE m_ePersonType;
    union
    {
        int SudentId;                       //学生Id
        std::string IdCard;                 //身份证号码
        ALIEN_INFO tAlien_Info;             //外地人
    };
};

/// <summary>
/// 测试函数
/// </summary>
int Test01() throw()
{
    try
    {
        CPerson cPerson01(48);
        CPerson cPerson02("51032289326778252242");
        CPerson cPerson03("四川省成都市", "18566668888");

        cPerson01.Printf();
        std::cout << '\n';

        cPerson02.Printf();
        std::cout << '\n';

        cPerson03.Printf();
        std::cout << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

int main()
{
    Test01();

    return EXIT_SUCCESS;
}

