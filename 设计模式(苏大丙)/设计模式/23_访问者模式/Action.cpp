#include "Action.h"
#include "Member.h"

void CAngry::MaleDothing(CAbstractMember* _pAbstractMember)
{
	std::cout << _pAbstractMember->GetName() << "男性角色生气" << std::endl;
}

void CAngry::FemaleDothing(CAbstractMember* _pAbstractMember)
{
	std::cout << _pAbstractMember->GetName() << "女性角色生气" << std::endl;
}

void CFear::MaleDothing(CAbstractMember* _pAbstractMember)
{
	std::cout << _pAbstractMember->GetName() << "男性角色恐惧" << std::endl;
}

void CFear::FemaleDothing(CAbstractMember* _pAbstractMember)
{
	std::cout << _pAbstractMember->GetName() << "女性角色恐惧" << std::endl;
}
