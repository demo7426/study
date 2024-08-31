//文件描述：
//      实现一个中介者模块
//作者：钱锐
//时间：2024/2/26
//修改记录：
//      2024/2/26     新建

#pragma once
#include <iostream>
#include <map>

using namespace std;

class CAbstractCountry;
class CAbstractMediator
{
public:
	virtual ~CAbstractMediator() {}

	//添加成员
	int AddMember(CAbstractCountry* _pAbstractCountry);

	/// <summary>
	/// 向其它国家宣布信息
	/// </summary>
	/// <param name="_DesCountryName">信息发送目的国家名称</param>
	/// <param name="_Msg">发送信息</param>
	virtual void DeclareMsg(string _DesCountryName, string _Msg) = 0;

protected:
	map<string, CAbstractCountry*> m_mapCountryInfo;
};

class CMediator01: public CAbstractMediator
{
public:
	~CMediator01(){}

	/// <summary>
	/// 向其它国家宣布信息
	/// </summary>
	/// <param name="_DesCountryName">信息发送目的国家名称</param>
	/// <param name="_Msg">发送信息</param>
	void DeclareMsg(string _DesCountryName, string _Msg) override;
};

