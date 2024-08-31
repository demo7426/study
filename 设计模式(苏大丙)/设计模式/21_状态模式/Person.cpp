#include "Person.h"

CAbstractPerson::~CAbstractPerson()
{
	if (m_pcAbstractState != nullptr)
	{
		delete m_pcAbstractState;
		m_pcAbstractState = nullptr;
	}
}

void CAbstractPerson::SetCAbstractState(CAbstractState* _pAbstractState)
{
	if (m_pcAbstractState != nullptr)
	{
		delete m_pcAbstractState;
		m_pcAbstractState = nullptr;
	}

	m_pcAbstractState = _pAbstractState;
}
