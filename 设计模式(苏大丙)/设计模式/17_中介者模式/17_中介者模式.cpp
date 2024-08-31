//文件描述：
//      实现一个中介者模式（类似于租户、中介、房东，中介可以自定义与租户、房东的交互方式）
//作者：钱锐
//时间：2024/2/26
//修改记录：
//      2024/2/26     新建

#include <iostream>
#include "Country.h"
#include "Mediator.h"

void Test01()
{
	CAbstractMediator* pcAbstractMediator = new CMediator01();
	CAbstractCountry* pcChina = new CChina("China", pcAbstractMediator);
	CAbstractCountry* pcAmerica = new CAmerica("America", pcAbstractMediator);

	pcChina->DeclareMsg(pcAmerica->GetCountryName(), "你们都是资本家、剥削者。");

	delete pcAmerica;
	delete pcChina;
	delete pcAbstractMediator;
}

int main()
{
	Test01();
	return 0;
}
