//文件描述：
//      实现一个状态模式（不同的状态之间有一定的联系）
//作者：钱锐
//时间：2024/2/28
//修改记录：
//      2024/2/28     新建

#include <iostream>
#include "Person.h"
#include "State.h"

int main()
{
	CAbstractPerson* pcPerson01 = new CPerson01;
	int nTimes[] = { 3, 9, 12, 15, 19, 24 };

	for (auto& item : nTimes)
	{
		pcPerson01->SetCurTimeClock(item);
		pcPerson01->Working();
	}

	delete pcPerson01;

	return 0;
}


