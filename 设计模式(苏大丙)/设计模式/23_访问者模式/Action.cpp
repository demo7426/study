#include "Action.h"
#include "Member.h"

void CAngry::MaleDothing(CAbstractMember* _pAbstractMember)
{
	std::cout << _pAbstractMember->GetName() << "���Խ�ɫ����" << std::endl;
}

void CAngry::FemaleDothing(CAbstractMember* _pAbstractMember)
{
	std::cout << _pAbstractMember->GetName() << "Ů�Խ�ɫ����" << std::endl;
}

void CFear::MaleDothing(CAbstractMember* _pAbstractMember)
{
	std::cout << _pAbstractMember->GetName() << "���Խ�ɫ�־�" << std::endl;
}

void CFear::FemaleDothing(CAbstractMember* _pAbstractMember)
{
	std::cout << _pAbstractMember->GetName() << "Ů�Խ�ɫ�־�" << std::endl;
}
