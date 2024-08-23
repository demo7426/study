#ifndef ASSIGNEDVALUE_H
#define ASSIGNEDVALUE_H

#include <QObject>
#include<QString>
#include<QPushButton>
#include<list>
#include<QTextEdit>

extern QTextEdit* m_pLCDNumber;
//对缓冲区进行赋值的类
class AssignedAndCaculate : public QObject
{
    Q_OBJECT
public:
    explicit AssignedAndCaculate(QObject *parent = nullptr);
    ~AssignedAndCaculate();

    QString m_strBuf;//字符串缓冲区，用于放置需要计算的内容
    double m_dbResults;//最终计算结果
    void Assignment();//将每一次的操作放到字符串中保存起来
    void Caculate();//对字符串进行计算
    void Clear();
private:
    bool Is_Isdent(QChar c);
    int ParsingString_Into_ListContainer(const QString TargetStr, QList<QString>* ListStr);
signals:

};

#endif // ASSIGNEDVALUE_H
