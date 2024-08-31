//文件描述：
//      实现一个观察者模式（发布-订阅机制）
//作者：钱锐
//时间：2024/2/27
//修改记录：
//      2024/2/27     新建

#include <iostream>

#include "Publisher.h"
#include "Observer.h"

void Test01()
{
    CAbstractPublisher* pcOfficial = new COfficialPublisher;
    CAbstractPublisher* pcGossip = new CGossipPublisher;

    CAbstractObserver* pcTeacher = new CTeacherObserver("化学老师", pcOfficial);
    CAbstractObserver* pcDoctor = new CDoctorObserver("牙科医生", pcOfficial);
    CAbstractObserver* pcNurse = new CNurseObserver("住院部护士", pcGossip);

    pcOfficial->Notify("学习新思想，争做急先锋。");
    pcGossip->Notify("xxx和xxx分居两地。");

    delete pcOfficial;
    delete pcGossip;
    delete pcTeacher;
    delete pcDoctor;
    delete pcNurse;

}

int main()
{
    Test01();
    return 0;
}


