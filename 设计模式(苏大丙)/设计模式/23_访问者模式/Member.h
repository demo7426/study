//�ļ�������
//      ʵ��һ����Աģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/29
//�޸ļ�¼��
//      2024/2/29     �½�

#pragma once
#include <iostream>
#include "Action.h"

class CAbstractMember
{
public:
	CAbstractMember(std::string _Name) : m_strName(_Name) {}
	virtual ~CAbstractMember() {}

 	inline std::string GetName() const
	{
		return m_strName;
	}

	virtual void Accept(CAbstractAction* _pAbstractAction) = 0;

protected:
	std::string m_strName = std::string();
};


class CMaleMember : public CAbstractMember
{
public:
	using CAbstractMember::CAbstractMember;
	void Accept(CAbstractAction* _pAbstractAction) override;
};

class CFemaleMember : public CAbstractMember
{
public:
	using CAbstractMember::CAbstractMember;
	void Accept(CAbstractAction* _pAbstractAction) override;
};
