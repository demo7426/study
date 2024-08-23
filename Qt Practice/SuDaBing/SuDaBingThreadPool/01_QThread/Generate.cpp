#include "Generate.h"
#include <QDebug>
#include <QElapsedTimer>

CGenerate::CGenerate(CAbstractDataSort* _pDataSort, QObject *parent)
    : m_pcDataSort(_pDataSort) , QThread{parent}
{}

CGenerate::~CGenerate()
{
    if(m_pcDataSort != nullptr)
    {
        m_pcDataSort->quit();
        m_pcDataSort->wait();
        m_pcDataSort->deleteLater();
    }
}

void CGenerate::run()
{
    srand(time(NULL));                  //保证随机数是随机产生的

    QVector<int> cQVecRandomNum;        //暂存生成的随机数
    QElapsedTimer cQElapsedTimer;

    //产生随机数

    cQElapsedTimer.start();
    for (unsigned int i = 0; i < m_unRandomNumCount; ++i) {
        cQVecRandomNum.push_back(rand() % m_unRandomNumCount);
    }

    qDebug() << "线程Id为 " << QThread::currentThreadId() << "生成了" << m_unRandomNumCount << "个随机数所耗的时间为" << cQElapsedTimer.elapsed() << "ms";

    emit sendRandomNum(cQVecRandomNum);

    //进行数据排序
    try
    {
        if(m_pcDataSort == nullptr)
            throw new std::exception();

        //确保新创建的线程排序结束后会发出信号
        connect(m_pcDataSort, &CAbstractDataSort::SendOutputData, this, &CGenerate::sendSortNum);

        m_pcDataSort->setInputData(cQVecRandomNum);
        m_pcDataSort->start();
    }
    catch (std::exception)
    {
        qDebug() << "排序指针对象为nullptr";
    }
}

void CGenerate::SetGenerateNum(unsigned int _Num) noexcept
{
    m_unRandomNumCount = _Num;
}

