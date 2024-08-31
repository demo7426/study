//文件描述：
//      实现一个国家类模块
//作者：钱锐
//时间：2024/2/26
//修改记录：
//      2024/2/26     新建

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
	/// 向其它国家宣布信息
	/// </summary>
	/// <param name="_DesCountryName">信息发送目的国家名称</param>
	/// <param name="_Msg">发送信息</param>
	virtual void DeclareMsg(std::string _DesCountryName, std::string _Msg) = 0;

	virtual void ReciveMsg(std::string _SrcCountryName, std::string _Msg) = 0;

	//获取国家名字
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

