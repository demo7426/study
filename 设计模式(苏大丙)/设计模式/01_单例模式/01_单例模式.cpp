//文件描述：
//      单例设计模式（包括饿汉模式、懒汉模式（使用原子变量双重检查或局部静态变量解决线程安全问题））
//作者：钱锐
//时间：2024/1/17
//修改记录：
//      2024/1/17     新建

#include <iostream>
#include <mutex>
#include <atomic>
using namespace std;

#if 0   //饿汉模式
class CTaskQueue
{
public:
    static CTaskQueue* GetInstance()
    {
        return m_pcTaskQ;
    }
    
    void Printf(string _Context)
    {
        cout << _Context << '\n';
    }
private:
    CTaskQueue() = default;
    CTaskQueue(const CTaskQueue& _TaskQ) = default;
    CTaskQueue& operator=(CTaskQueue& t) = default;

    static CTaskQueue* m_pcTaskQ;
};
CTaskQueue* CTaskQueue::m_pcTaskQ = new CTaskQueue();


#else   //懒汉模式
class CTaskQueue
{
public:
    static CTaskQueue* GetInstance()
    {
        
#if 0   //使用原子变量双重检查解决线程安全问题
        CTaskQueue* pcTaskQ = m_pcTaskQ.load();

        if (pcTaskQ == nullptr)
        {
            m_mutex.lock();

            pcTaskQ = m_pcTaskQ.load();
            if (m_pcTaskQ == nullptr)
            {
                pcTaskQ = new CTaskQueue();
                m_pcTaskQ.store(pcTaskQ); 
            }

            m_mutex.unlock();
        }
        return pcTaskQ;

#else   //使用局部静态变量解决线程安全问题（要求g++为11标准以上）
        //因为11标准以上规定如果指令逻辑进入了一个未被初始化的变量，所有并发应当等待该变量完成初始化
        static CTaskQueue cTaskQ;
        return &cTaskQ;
#endif
    }

    void Printf(string _Context)
    {
        cout << _Context << '\n';
    }
private:
    CTaskQueue() = default;
    CTaskQueue(const CTaskQueue& _TaskQ) = default;
    CTaskQueue& operator=(CTaskQueue& t) = default;

    static atomic<CTaskQueue*> m_pcTaskQ;
    static mutex m_mutex;
};
atomic<CTaskQueue*> CTaskQueue::m_pcTaskQ;
mutex CTaskQueue::m_mutex;
#endif

int main(int argc, char *argv[], char *envp[])
{
    CTaskQueue* pcTaskQ = CTaskQueue::GetInstance();
    pcTaskQ->Printf("Printf called.");

    return 0;
}
