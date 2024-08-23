#ifndef CABSTRACTDATASORT_H
#define CABSTRACTDATASORT_H

#include <QThread>
#include <QVector>

//排序基类
class CAbstractDataSort : public QThread
{
    Q_OBJECT
public:
    explicit CAbstractDataSort(QObject *parent = nullptr);
    virtual ~CAbstractDataSort() = 0;

    void setInputData(const QVector<int>& _QVecInfo);       //设置待排序的数据

protected:
    QVector<int> m_cQVecData;

signals:
    void SendOutputData(const QVector<int>&);               //排序完成，并将数据传出

};


class CBubbleDataSort : public CAbstractDataSort
{
public:
    using CAbstractDataSort::CAbstractDataSort;

protected:
    void run() final;                                       //重写QThread内部的run方法

};

class CQuickDataSort : public CAbstractDataSort
{
public:
    using CAbstractDataSort::CAbstractDataSort;

protected:
    void run() final;                                       //重写QThread内部的run方法

private:
    int quick_sort(QVector<int>& a, int low, int high);
};

#endif // CABSTRACTDATASORT_H

