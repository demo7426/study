//�ļ�������
//      ʵ��һ����Ϊģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/29
//�޸ļ�¼��
//      2024/2/29     �½�

#pragma once

class CAbstractMember;

//��Ϊ����
class CAbstractAction
{
public:
	virtual ~CAbstractAction(){}
	virtual void MaleDothing(CAbstractMember* _pAbstractMember) = 0;
	virtual void FemaleDothing(CAbstractMember* _pAbstractMember) = 0;
};

class CAngry : public CAbstractAction
{
public:
	void MaleDothing(CAbstractMember* _pAbstractMember) override;
	void FemaleDothing(CAbstractMember* _pAbstractMember) override;
};

class CFear : public CAbstractAction
{
public:
	void MaleDothing(CAbstractMember* _pAbstractMember) override;
	void FemaleDothing(CAbstractMember* _pAbstractMember) override;
};

