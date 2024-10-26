#include <QThread>
#include <thread>

#include "diceobject.h"

#define USER_EXIR_SUCCESS 0
#define USER_EXIR_FAILURE -2

CDiceObject::CDiceObject(QObject *parent)
    : QObject{parent}
{
    //取消自动删除，如果启用了自动删除，QThreadPool将在调用run（）后自动删除这个可运行对象；否则，所有权仍然属于应用程序程序员。
    //防止误删除不属于自己的对象（比如当前的MainWindow类内部对象被自动删除后，会导致内存异常进而程序崩溃）。
    setAutoDelete(false);
}

void CDiceObject::StartThread(void)
{
    m_bStop = false;
}

int CDiceObject::StartThrowDice()
{
    m_bPause = false;

    return USER_EXIR_SUCCESS;
}

int CDiceObject::StopThrowDice()
{
    m_bPause = true;

    return USER_EXIR_SUCCESS;
}

void CDiceObject::StopThread()
{
    m_bStop = true;
    m_unCurFreq = 0;
}

void CDiceObject::run()
{
    while (!m_bStop)
    {
        if(m_bPause)
            continue;

        m_unCurFreq++;
        emit SendCurMsg(m_unCurFreq, rand() % 6 + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
