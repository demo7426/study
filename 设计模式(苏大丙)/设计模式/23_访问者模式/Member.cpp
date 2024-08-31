#include "Member.h"

void CMaleMember::Accept(CAbstractAction* _pAbstractAction)
{
	_pAbstractAction->MaleDothing(this);
}

void CFemaleMember::Accept(CAbstractAction* _pAbstractAction)
{
	_pAbstractAction->FemaleDothing(this);
}
