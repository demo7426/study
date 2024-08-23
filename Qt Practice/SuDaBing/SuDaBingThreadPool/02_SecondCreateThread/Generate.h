#ifndef CMYTHREAD_H
#define CMYTHREAD_H

#include <QVector>

#include "DataSort.h"

class CGenerate : public QObject
{
    Q_OBJECT
public:
    CGenerate() = delete;
    CGenerate(const CGenerate&) = delete;
    explicit CGenerate(CAbstractDataSort* _pDataSort, QObject *parent = nullptr);
    ~CGenerate();

public slots:
    void Run(unsigned int _Count);                          //开始排序

private:
    CAbstractDataSort* m_pcDataSort = nullptr;              //排序指针对象

signals:
    void sendRandomNum(QVector<int>);                       //排序前的数据
    void sendSortNum(QVector<int>);                         //排序后的数据
};

#endif // CMYTHREAD_H
