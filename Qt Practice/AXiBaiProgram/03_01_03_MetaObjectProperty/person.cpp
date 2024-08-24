/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	person.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.24
描  述:	实现对person信息的控制
备  注:
修改记录:

  1.  日期: 2024.08.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/


#include "person.h"

CPerson::CPerson(QObject *parent)
    : QObject{parent}
{}

void CPerson::SetName(QString _Name) noexcept
{
    m_StrName = _Name;
    emit NameChanged(_Name);        //手动发出信号
}

void CPerson::SetAge(int _Age) noexcept
{
    if(_Age >= 0 && _Age <= 200)
    {
        m_nAge = _Age;
        emit AgeChanged(_Age);      //手动发出信号
    }
}

void CPerson::SetScore(int _Socre) noexcept
{
    if(_Socre >= 0 && _Socre <= 100)
    {
        m_nScore = _Socre;
        emit ScoreChanged(_Socre);  //手动发出信号
    }
}


