#include "Observer.h"

void CTeacherObserver::Updata(string _Msg)
{
	cout << m_strName << " recive: " << _Msg << endl;
}

void CDoctorObserver::Updata(string _Msg)
{
	cout << m_strName << " recive: " << _Msg << endl;
}

void CNurseObserver::Updata(string _Msg)
{
	cout << m_strName << " recive: " << _Msg << endl;
}
