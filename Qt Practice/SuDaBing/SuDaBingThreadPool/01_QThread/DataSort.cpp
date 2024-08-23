#include "DataSort.h"
#include <QDebug>
#include <QElapsedTimer>

CAbstractDataSort::CAbstractDataSort(QObject *parent)
    : QThread{parent}
{}

void CAbstractDataSort::setInputData(const QVector<int> &_QVecInfo)
{
    this->m_cQVecData = _QVecInfo;
}

CAbstractDataSort::~CAbstractDataSort(){}

void CBubbleDataSort::run()
{
    QElapsedTimer cQElapsedTimer;

    cQElapsedTimer.start();
    int nTemp = 0;
    for (int i = 0; i < m_cQVecData.size() - 1; ++i)
    {
        for (int j = 0; j < m_cQVecData.size() - 1 - i; ++j)
        {
            if(m_cQVecData[j] > m_cQVecData[j + 1])
            {
                nTemp = m_cQVecData[j];
                m_cQVecData[j] = m_cQVecData[j + 1];
                m_cQVecData[j + 1] = nTemp;
            }
        }
    }

    qDebug() << "线程Id为 " << QThread::currentThreadId() << "冒泡排序耗时为：" << cQElapsedTimer.elapsed() << "ms";

    emit SendOutputData(m_cQVecData);
}

void CQuickDataSort::run()
{
    QElapsedTimer cQElapsedTimer;

    cQElapsedTimer.start();
    quick_sort(m_cQVecData, 0, m_cQVecData.size() - 1);

    qDebug() << "线程Id为 " << QThread::currentThreadId() << "快速排序耗时为：" << cQElapsedTimer.elapsed() << "ms";

    emit SendOutputData(m_cQVecData);
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
