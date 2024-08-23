#ifndef CMYTHREAD_H
#define CMYTHREAD_H

#include <QThread>
#include <QVector>

#include "DataSort.h"

class CGenerate : public QThread
{
    Q_OBJECT
public:
    CGenerate() = delete;
    CGenerate(const CGenerate&) = delete;
    explicit CGenerate(CAbstractDataSort* _pDataSort, QObject *parent = nullptr);
    ~CGenerate();

public slots:
    void SetGenerateNum(unsigned int _Num) noexcept ;       //设置随机数个数

protected:
    void run() override;

private:
    CAbstractDataSort* m_pcDataSort = nullptr;              //排序指针对象
    unsigned int m_unRandomNumCount = 0;                    //随机数个数

signals:
    void sendRandomNum(QVector<int>);                       //排序前的数据
    void sendSortNum(QVector<int>);                         //排序后的数据
};

#endif // CMYTHREAD_H
