#include <QThread>
#include <thread>
#include <QSemaphore>

#include "diceobject.h"

#define USER_EXIR_SUCCESS 0
#define USER_EXIR_FAILURE -2

quint32 g_unCurFreq = 0;            //次数
quint32 g_unCount = 0;              //总数
QVector<quint32> g_vecBufData;         //缓冲区数据

QSemaphore g_cSemaphoreProducer(0);
QSemaphore g_cSemaphoreConsumer(0);

CDiceProducer::CDiceProducer(QObject *parent)
    : QThread{parent}
{}
void CDiceProducer::StartThread(void)
{
    g_unCurFreq = 0;
    g_unCount = 0;
    g_vecBufData.clear();

    //启动生产者线程
    if(g_cSemaphoreConsumer.available() == 0)
        g_cSemaphoreConsumer.release(1);

    //保证生产者线程最多只会被手动启动一次
    if(g_cSemaphoreConsumer.available() > 1)
    {
        int nAvailable = g_cSemaphoreConsumer.available();
        g_cSemaphoreConsumer.release(nAvailable - 1);
        g_cSemaphoreConsumer.acquire(nAvailable);               //防止线程被多次唤醒
    }

    this->start();
}

void CDiceProducer::StopThread()
{
    g_unCurFreq = 0;

    int nAvailable = g_cSemaphoreProducer.available();
    if(nAvailable > 0)
    {
        g_cSemaphoreProducer.release(nAvailable);
        g_cSemaphoreProducer.acquire(nAvailable);               //防止线程被多次唤醒
    }

    this->terminate();
    this->wait();
}

void CDiceProducer::run()
{
    while (true)
    {
        emit SendCurState(STATE::WAIT);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        g_cSemaphoreConsumer.acquire(1);
        emit SendCurState(STATE::RUN);
        g_unCurFreq++;

        for (int i = 0; i < 10; ++i) {
            g_vecBufData.push_back(++g_unCount);
        }

        g_cSemaphoreProducer.release(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


CDiceConsumer::CDiceConsumer(QObject *parent)
    :QThread(parent)
{}

void CDiceConsumer::StartThread()
{
    this->start();
}

void CDiceConsumer::StopThread()
{
    int nAvailable = g_cSemaphoreConsumer.available();
    if(nAvailable > 0)
    {
        g_cSemaphoreProducer.release(nAvailable);
        g_cSemaphoreProducer.acquire(nAvailable);               //防止线程被多次唤醒
    }

    this->terminate();
    this->wait();
}

void CDiceConsumer::run()
{
    while (true)
    {
        emit SendCurState(STATE::WAIT);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        g_cSemaphoreProducer.acquire(1);
        emit SendCurState(STATE::RUN);

        emit SendCurMsg(g_unCurFreq, g_vecBufData);
        g_vecBufData.clear();

        g_cSemaphoreConsumer.release(1);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
