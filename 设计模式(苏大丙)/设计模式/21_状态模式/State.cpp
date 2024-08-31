#include "State.h"
#include "Person.h"



void CForenoon::Working(CAbstractPerson* _pAbstractPerson)
{
	int nTime = _pAbstractPerson->GetCurTimeClock();

	if (nTime > 6 && nTime < 11)
	{
		std::cout << "�������......" << std::endl;
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
		std::cout << "�������......" << std::endl;
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
		std::cout << "���������......" << std::endl;
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
		std::cout << "�������......" << std::endl;
	}
	else
	{
		std::cout << "˯������......" << std::endl;
	}
}
