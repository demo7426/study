#include <QThread>
#include <thread>
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>

#include "diceobject.h"

#define USER_EXIR_SUCCESS 0
#define USER_EXIR_FAILURE -2

quint32 g_unCurFreq = 0;            //次数
quint32 g_unCurRandom = 0;          //随机数

QMutex g_cMutex;
QWaitCondition g_cWaitCondition;

CDiceProducer::CDiceProducer(QObject *parent)
    : QObject{parent}
{}
void CDiceProducer::StartThread(void)
{
    m_bStop = false;
}

void CDiceProducer::StopThread()
{
    m_bStop = true;
    g_unCurFreq = 0;
}

void CDiceProducer::Run()
{
    while (!m_bStop)
    {
        g_cMutex.lock();
        g_unCurFreq++;
        g_unCurRandom = rand() % 6 + 1;
        g_cWaitCondition.notify_one();
        g_cMutex.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}


CDiceConsumer::CDiceConsumer(QObject *parent)
    :QObject(parent)
{}

void CDiceConsumer::StartThread()
{
    m_bStop = false;
}

void CDiceConsumer::StopThread()
{
    m_bStop = true;
    g_cWaitCondition.notify_one();          //唤醒休眠的线程
}

void CDiceConsumer::Run()
{
    while (!m_bStop)
    {
        {
            QMutexLocker locker(&g_cMutex);
            g_cWaitCondition.wait(&g_cMutex);

            if(m_bStop)                         //保证程序可以正常退出
                break;

            emit SendCurMsg(g_unCurFreq, g_unCurRandom);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
