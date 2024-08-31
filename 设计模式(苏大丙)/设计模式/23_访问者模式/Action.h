//文件描述：
//      实现一个行为模块
//作者：钱锐
//时间：2024/2/29
//修改记录：
//      2024/2/29     新建

#pragma once

class CAbstractMember;

//行为基类
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

