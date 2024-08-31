//�ļ�������
//      ʵ��һ���н���ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/26
//�޸ļ�¼��
//      2024/2/26     �½�

#pragma once
#include <iostream>
#include <map>

using namespace std;

class CAbstractCountry;
class CAbstractMediator
{
public:
	virtual ~CAbstractMediator() {}

	//��ӳ�Ա
	int AddMember(CAbstractCountry* _pAbstractCountry);

	/// <summary>
	/// ����������������Ϣ
	/// </summary>
	/// <param name="_DesCountryName">��Ϣ����Ŀ�Ĺ�������</param>
	/// <param name="_Msg">������Ϣ</param>
	virtual void DeclareMsg(string _DesCountryName, string _Msg) = 0;

protected:
	map<string, CAbstractCountry*> m_mapCountryInfo;
};

class CMediator01: public CAbstractMediator
{
public:
	~CMediator01(){}

	/// <summary>
	/// ����������������Ϣ
	/// </summary>
	/// <param name="_DesCountryName">��Ϣ����Ŀ�Ĺ�������</param>
	/// <param name="_Msg">������Ϣ</param>
	void DeclareMsg(string _DesCountryName, string _Msg) override;
};

