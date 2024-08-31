#include "State.h"
#include "Person.h"



void CForenoon::Working(CAbstractPerson* _pAbstractPerson)
{
	int nTime = _pAbstractPerson->GetCurTimeClock();

	if (nTime > 6 && nTime < 11)
	{
		std::cout << "制作早餐......" << std::endl;
	}
	else
	{
		_pAbstractPerson->SetCAbstractState(new Cnoon);
		_pAbstractPerson->Working();
	}

}

void Cnoon::Working(CAbstractPerson* _pAbstractPerson)
{
	int nTime = _pAbstractPerson->GetCurTimeClock();

	if (nTime >= 11 && nTime <= 13)
	{
		std::cout << "制作午餐......" << std::endl;
	}
	else
	{
		_pAbstractPerson->SetCAbstractState(new CAfternoon);
		_pAbstractPerson->Working();
	}
}

void CAfternoon::Working(CAbstractPerson* _pAbstractPerson)
{
	int nTime = _pAbstractPerson->GetCurTimeClock();

	if (nTime > 13 && nTime < 18)
	{
		std::cout << "制作下午茶......" << std::endl;
	}
	else
	{
		_pAbstractPerson->SetCAbstractState(new CEvening);
		_pAbstractPerson->Working();
	}
}

void CEvening::Working(CAbstractPerson* _pAbstractPerson)
{
	int nTime = _pAbstractPerson->GetCurTimeClock();

	if (nTime >= 18 && nTime < 21)
	{
		std::cout << "制作晚餐......" << std::endl;
	}
	else
	{
		std::cout << "睡觉，晚安......" << std::endl;
	}
}
