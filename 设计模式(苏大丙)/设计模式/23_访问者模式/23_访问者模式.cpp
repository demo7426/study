//文件描述：
//      实现一个访问者模式（二分：先分离对象、再分离对象行为，该模式实际应用范围较为狭窄）
//作者：钱锐
//时间：2024/2/29
//修改记录：
//      2024/2/29     新建

#include <iostream>
#include <list>
#include <vector>

#include "Member.h"
#include "Action.h"

class CMemberTest
{
public:
    CMemberTest()
    {
        m_vecAction.push_back(new CAngry);
        m_vecAction.push_back(new CFear);
    }

    ~CMemberTest()
    {
        for (const auto& item : m_listMember)
            delete item;

        for (const auto& item : m_vecAction)
            delete item;
    }

    void AddMember(CAbstractMember* _pAbstractMember)
    {
        m_listMember.push_back(_pAbstractMember);
    }
    
    void RemoveMember(CAbstractMember* _pAbstractMember)
    {
        m_listMember.remove(_pAbstractMember);
    }

    void Display()
    {
        for (const auto& item : m_listMember)
        {
            int nIndex = rand() % m_vecAction.size();
            item->Accept(m_vecAction.at(nIndex));
        }
    }

private:
    std::vector<CAbstractAction*> m_vecAction;
    std::list<CAbstractMember*> m_listMember;
};

int main()
{
    srand(time(NULL));

    CMemberTest cMemberTest;
    cMemberTest.AddMember(new CMaleMember("路飞"));
    cMemberTest.AddMember(new CMaleMember("乌索普"));
    cMemberTest.AddMember(new CMaleMember("乔巴"));
    cMemberTest.AddMember(new CMaleMember("山治"));
    cMemberTest.AddMember(new CFemaleMember("罗宾"));
    cMemberTest.AddMember(new CFemaleMember("娜美"));

    cMemberTest.Display();

    return 0;
}


