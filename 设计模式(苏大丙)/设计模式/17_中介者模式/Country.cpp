#include "Country.h"

void CChina::DeclareMsg(std::string _DesCountryName, std::string _Msg)
{
	std::cout << "China ����һ����Ϣ��" << std::endl;
	m_pcAbstractMediator->DeclareMsg(_DesCountryName, _Msg);
}

void CChina::ReciveMsg(std::string _SrcCountryName, std::string _Msg)
{
	std::cout << "China ����һ�����ԣ�"<< _SrcCountryName << "����ϢΪ��" << _Msg << std::endl;
}

void CFrench::DeclareMsg(std::string _DesCountryName, std::string _Msg)
{
	std::cout << "French ����һ����Ϣ��" << std::endl;
	m_pcAbstractMediator->DeclareMsg(_DesCountryName, _Msg);
}

void CFrench::ReciveMsg(std::string _SrcCountryName, std::string _Msg)
{
	std::cout << "French ����һ�����ԣ�" << _SrcCountryName << "����ϢΪ��" << _Msg << std::endl;
}

void CGermany::DeclareMsg(std::string _DesCountryName, std::string _Msg)
{
	std::cout << "Germany ����һ����Ϣ��" << std::endl;
	m_pcAbstractMediator->DeclareMsg(_DesCountryName, _Msg);
}

void CGermany::ReciveMsg(std::string _SrcCountryName, std::string _Msg)
{
	std::cout << "Germany ����һ�����ԣ�" << _SrcCountryName << "����ϢΪ��" << _Msg << std::endl;
}

void CAmerica::DeclareMsg(std::string _DesCountryName, std::string _Msg)
{
	std::cout << "America ����һ����Ϣ��" << std::endl;
	m_pcAbstractMediator->DeclareMsg(_DesCountryName, _Msg);
}

void CAmerica::ReciveMsg(std::string _SrcCountryName, std::string _Msg)
{
	std::cout << "America ����һ�����ԣ�" << _SrcCountryName << "����ϢΪ��" << _Msg << std::endl;
}
