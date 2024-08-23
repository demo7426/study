#ifndef CABSTRACTDATASORT_H
#define CABSTRACTDATASORT_H

#include <QObject>
#include <QVector>

//排序基类
class CAbstractDataSort : public QObject
{
    Q_OBJECT
public:
    CAbstractDataSort() = default;
    //explicit CAbstractDataSort(QObject *parent = nullptr);  //CAbstractDataSort该类会被线程使用，所以不能指定父类对象
    virtual ~CAbstractDataSort() = 0;

    virtual void Sort(QVector<int> _QVecInfo) = 0;          //设置待排序的数据

signals:
    void SendOutputData(QVector<int>);                       //排序完成，并将数据传出

};


class CBubbleDataSort : public CAbstractDataSort
{
public:
    using CAbstractDataSort::CAbstractDataSort;

    void Sort(QVector<int> _QVecInfo) final;                 //重写QThread内部的run方法

};

class CQuickDataSort : public CAbstractDataSort
{
public:
    using CAbstractDataSort::CAbstractDataSort;

    void Sort(QVector<int> _QVecInfo) final;                                       //重写QThread内部的run方法

private:
    int quick_sort(QVector<int>& a, int low, int high);
};

#endif // CABSTRACTDATASORT_H

