#include "Country.h"

void CChina::DeclareMsg(std::string _DesCountryName, std::string _Msg)
{
	std::cout << "China 宣布一个消息：" << std::endl;
	m_pcAbstractMediator->DeclareMsg(_DesCountryName, _Msg);
}

void CChina::ReciveMsg(std::string _SrcCountryName, std::string _Msg)
{
	std::cout << "China 接收一个来自："<< _SrcCountryName << "，消息为：" << _Msg << std::endl;
}

void CFrench::DeclareMsg(std::string _DesCountryName, std::string _Msg)
{
	std::cout << "French 宣布一个消息：" << std::endl;
	m_pcAbstractMediator->DeclareMsg(_DesCountryName, _Msg);
}

void CFrench::ReciveMsg(std::string _SrcCountryName, std::string _Msg)
{
	std::cout << "French 接收一个来自：" << _SrcCountryName << "，消息为：" << _Msg << std::endl;
}

void CGermany::DeclareMsg(std::string _DesCountryName, std::string _Msg)
{
	std::cout << "Germany 宣布一个消息：" << std::endl;
	m_pcAbstractMediator->DeclareMsg(_DesCountryName, _Msg);
}

void CGermany::ReciveMsg(std::string _SrcCountryName, std::string _Msg)
{
	std::cout << "Germany 接收一个来自：" << _SrcCountryName << "，消息为：" << _Msg << std::endl;
}

void CAmerica::DeclareMsg(std::string _DesCountryName, std::string _Msg)
{
	std::cout << "America 宣布一个消息：" << std::endl;
	m_pcAbstractMediator->DeclareMsg(_DesCountryName, _Msg);
}

void CAmerica::ReciveMsg(std::string _SrcCountryName, std::string _Msg)
{
	std::cout << "America 接收一个来自：" << _SrcCountryName << "，消息为：" << _Msg << std::endl;
}
