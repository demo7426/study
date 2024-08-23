#include "DataSort.h"
#include <QDebug>
#include <QElapsedTimer>
#include <QThread>

CAbstractDataSort::~CAbstractDataSort(){}

void CBubbleDataSort::Sort(QVector<int> _QVecInfo)
{
    QElapsedTimer cQElapsedTimer;

    cQElapsedTimer.start();
    int nTemp = 0;
    for (int i = 0; i < _QVecInfo.size() - 1; ++i)
    {
        for (int j = 0; j < _QVecInfo.size() - 1 - i; ++j)
        {
            if(_QVecInfo[j] > _QVecInfo[j + 1])
            {
                nTemp = _QVecInfo[j];
                _QVecInfo[j] = _QVecInfo[j + 1];
                _QVecInfo[j + 1] = nTemp;
            }
        }
    }

    qDebug() << "线程Id为 " << QThread::currentThreadId() << "冒泡排序耗时为：" << cQElapsedTimer.elapsed() << "ms";

    emit SendOutputData(_QVecInfo);
}

void CQuickDataSort::Sort(QVector<int> _QVecInfo)
{
    QElapsedTimer cQElapsedTimer;

    cQElapsedTimer.start();
    quick_sort(_QVecInfo, 0, _QVecInfo.size() - 1);

    qDebug() << "线程Id为 " << QThread::currentThreadId() << "快速排序耗时为：" << cQElapsedTimer.elapsed() << "ms";

    emit SendOutputData(_QVecInfo);
}


//快速排序法
int CQuickDataSort::quick_sort(QVector<int>& a, int low, int high)
{
    int i = low;	//第一位
    int j = high;	//最后一位
    int key = a[i]; //将第一个数作为基准值-- 先找到一个基准值

    while (i < j)
    {
        while(i < j && a[j] >= key)
        {
            j--;
        }
        a[i] = a[j];

        while(i < j && a[i] <= key)
        {
            i++;
        }
        a[j] = a[i];
    }
    a[i] = key;
    if (i-1 > low)
    {
        quick_sort(a, low, i-1);
    }

    if (i+1 < high)
    {
        quick_sort(a, i+1, high);
    }

    return 0;
}
