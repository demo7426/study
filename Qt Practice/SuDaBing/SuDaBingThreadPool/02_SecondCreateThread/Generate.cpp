#include "Generate.h"
#include <QDebug>
#include <QElapsedTimer>
#include <QThread>

CGenerate::CGenerate(CAbstractDataSort* _pDataSort, QObject *parent)
    : m_pcDataSort(_pDataSort), QObject(parent)
{}

CGenerate::~CGenerate()
{
    if(m_pcDataSort != nullptr)
        m_pcDataSort->deleteLater();
}

void CGenerate::Run(unsigned int _Count)
{
    srand(time(NULL));                  //保证随机数是随机产生的

    QVector<int> cQVecRandomNum;        //暂存生成的随机数
    QElapsedTimer cQElapsedTimer;

    //产生随机数

    cQElapsedTimer.start();
    for (unsigned int i = 0; i < _Count; ++i) {
        cQVecRandomNum.push_back(rand() % _Count);
    }

    qDebug() << "线程Id为 " << QThread::currentThreadId() << "生成了" << _Count << "个随机数所耗的时间为" << cQElapsedTimer.elapsed() << "ms";

    emit sendRandomNum(cQVecRandomNum);
    //进行数据排序
    try
    {
        QThread *pcQThread = new QThread(this);

        if(m_pcDataSort == nullptr)
            throw new std::exception();

        //确保新创建的线程排序结束后会发出信号
        connect(m_pcDataSort, &CAbstractDataSort::SendOutputData, this, &CGenerate::sendSortNum);

        //TODO:不能在子线程里面将新的QObject对象移动到新的子线程中，移动只能在主线程中进行;
        m_pcDataSort->moveToThread(pcQThread);
        pcQThread->start();
        m_pcDataSort->Sort(cQVecRandomNum);
    }
    catch (std::exception)
    {
        qDebug() << "排序指针对象为nullptr";
    }
}

