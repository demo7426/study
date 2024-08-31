//�ļ�������
//      ʵ��һ��������ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/26
//�޸ļ�¼��
//      2024/2/26     �½�

#pragma once
#include <iostream>
#include "Mediator.h"

class CAbstractCountry
{
public:
	CAbstractCountry(std::string _CountryName, CAbstractMediator* _pAbstractMediator): m_strCountryName(_CountryName), m_pcAbstractMediator(_pAbstractMediator)
	{
		if (m_pcAbstractMediator != nullptr)
		{
			m_pcAbstractMediator->AddMember(this);
		}
	}
	virtual ~CAbstractCountry(){}

	/// <summary>
	/// ����������������Ϣ
	/// </summary>
	/// <param name="_DesCountryName">��Ϣ����Ŀ�Ĺ�������</param>
	/// <param name="_Msg">������Ϣ</param>
	virtual void DeclareMsg(std::string _DesCountryName, std::string _Msg) = 0;

	virtual void ReciveMsg(std::string _SrcCountryName, std::string _Msg) = 0;

	//��ȡ��������
	inline std::string GetCountryName() const
	{
		return m_strCountryName;
	}

protected:
	std::string m_strCountryName = std::string();
	CAbstractMediator* m_pcAbstractMediator = nullptr;
};

class CChina : public CAbstractCountry
{
public:
	using CAbstractCountry::CAbstractCountry;

	void DeclareMsg(std::string _DesCountryName, std::string _Msg) override;

	void ReciveMsg(std::string _SrcCountryName, std::string _Msg) override;
};

class CFrench : public CAbstractCountry
{
public:
	using CAbstractCountry::CAbstractCountry;

	void DeclareMsg(std::string _DesCountryName, std::string _Msg) override;

	void ReciveMsg(std::string _SrcCountryName, std::string _Msg) override;
};

class CGermany : public CAbstractCountry
{
public:
	using CAbstractCountry::CAbstractCountry;

	void DeclareMsg(std::string _DesCountryName, std::string _Msg) override;

	void ReciveMsg(std::string _SrcCountryName, std::string _Msg) override;
};

class CAmerica : public CAbstractCountry
{
public:
	using CAbstractCountry::CAbstractCountry;

	void DeclareMsg(std::string _DesCountryName, std::string _Msg) override;

	void ReciveMsg(std::string _SrcCountryName, std::string _Msg) override;
};

