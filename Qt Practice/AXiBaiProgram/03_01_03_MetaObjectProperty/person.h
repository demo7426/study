/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	person.h
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

#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class CPerson : public QObject
{
    Q_OBJECT

    //设置类属性
    Q_CLASSINFO("Author", "qianrui")
    Q_CLASSINFO("License", "GPL")
    Q_CLASSINFO("Version", "V0.1.0")
    Q_CLASSINFO("Description", "This is a CPerson class.")

    //设置字段的属性
    Q_PROPERTY(QString Name READ GetName WRITE SetName NOTIFY NameChanged FINAL)
    Q_PROPERTY(bool Sex MEMBER m_bSex NOTIFY SexChanged FINAL)
    Q_PROPERTY(int Age MEMBER m_nAge WRITE SetAge NOTIFY AgeChanged FINAL)
    Q_PROPERTY(int Score MEMBER m_nScore WRITE SetScore NOTIFY ScoreChanged FINAL)

public:
    explicit CPerson(QObject *parent = nullptr);

private:
    QString m_StrName;                                  //姓氏
    bool m_bSex;                                        //性别；是否未男性;true--男性;false--女性
    int m_nAge;                                         //年龄
    int m_nScore;                                       //分数

signals:
    void NameChanged(QString);                          //发出name被修改的信号
    void SexChanged(bool);                              //发出性别被修改的信号
    void AgeChanged(int);                               //发出age被修改的信号
    void ScoreChanged(int);                             //发出score被修改的信号

private:
    inline QString GetName(void) const
    {
        return m_StrName;
    }

    //设置姓氏
    void SetName(QString _Name) noexcept;

    //设置年龄
    void SetAge(int _Age) noexcept;

    //设置分数
    void SetScore(int _Socre) noexcept;
};

#endif // PERSON_H
