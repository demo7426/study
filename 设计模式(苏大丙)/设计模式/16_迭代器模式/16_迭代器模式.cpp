//文件描述：
//      实现一个迭代器模式（实现一个List容器及其迭代器）
//作者：钱锐
//时间：2024/2/23
//修改记录：
//      2024/2/23     新建

#include <iostream>
#include <vector>
#include "List.h"
#include "Iterator.h"

using namespace std;

void Test01()
{
    vector<string> vecName{ "张三","李四", "王五", "陈六" };
    CList cList;

    for (auto item : vecName)
        cList.PushBack(item);

    cout << "正序遍历：\n";
    CAbstractIterator* pcAbstractIterator = cList.GetIteratorInstance(false);

    for (pcAbstractIterator->First();  pcAbstractIterator->GetCurNode() != pcAbstractIterator->End(); )
    {
        cout << pcAbstractIterator->GetCurNode()->Data << " ";
        pcAbstractIterator->Next();
    }
    delete pcAbstractIterator;
    
    cout << "\n逆序遍历：\n";
    pcAbstractIterator = cList.GetIteratorInstance(true);

    for (pcAbstractIterator->First(); pcAbstractIterator->GetCurNode() != pcAbstractIterator->End(); pcAbstractIterator->Next())
    {
        cout << pcAbstractIterator->GetCurNode()->Data << " ";
    }
    delete pcAbstractIterator;

}

int main()
{
    Test01();
    return 0;
}
