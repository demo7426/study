#include "Mediator.h"
#include "Country.h"

int CAbstractMediator::AddMember(CAbstractCountry* _pAbstractCountry)
{
	if (m_mapCountryInfo.find(_pAbstractCountry->GetCountryName()) != m_mapCountryInfo.end())
		return -1;

	m_mapCountryInfo.insert(make_pair(_pAbstractCountry->GetCountryName(), _pAbstractCountry));
	return 0;
}

void CMediator01::DeclareMsg(string _DesCountryName, string _Msg)
{
	if (m_mapCountryInfo.find(_DesCountryName) == m_mapCountryInfo.end())
		return;

	m_mapCountryInfo[_DesCountryName]->ReciveMsg(m_mapCountryInfo[_DesCountryName]->GetCountryName(), _Msg);	
}
