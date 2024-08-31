//文件描述：
//      使用单例设计模式，实现一个支持多线程模式下的任务队列（暂未实现多线程同步）
//作者：钱锐
//时间：2024/1/18
//修改记录：
//      2024/1/18     新建
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
using namespace std;

//任务队列类
class CTaskQueue
{
public:
	static CTaskQueue* GetInstance()
	{
		return m_pcTaskQ;
	}

	bool Empty()
	{
		lock_guard<mutex> lock(m_mutex);
		return m_queue.empty();
	}

	//删除头部元素
	bool Pop()
	{
		lock_guard<mutex> lock(m_mutex);
		if (m_queue.empty())
			return false;

		m_queue.pop();
		return true;
	}

	int Front()
	{
		lock_guard<mutex> lock(m_mutex);
		if (!m_queue.empty())
		{
			return m_queue.front();
		}
	}

	void Push(int&& _Node)
	{
		lock_guard<mutex> lock(m_mutex);
		m_queue.push(_Node);
	}

private:
	CTaskQueue() = default;
	CTaskQueue(const CTaskQueue& _TaskQ) = default;
	CTaskQueue& operator=(CTaskQueue& _TaskQ) = default;

	static CTaskQueue* m_pcTaskQ;
	queue<int> m_queue;
	mutex m_mutex;
};
CTaskQueue* CTaskQueue::m_pcTaskQ = new CTaskQueue;

int main(int argc, char *argv[], char *enpv[])
{
	CTaskQueue* pcTaskQ = CTaskQueue::GetInstance();

	thread th1(
		[=]()
		{
			for (int i = 0; i < 10; i++)
			{
				this_thread::sleep_for(std::chrono::microseconds(10));
				pcTaskQ->Push(i + 100);
				cout << "Push " << i + 100 << '\n';
			}
		}
	);

	thread th2(
		[=]()
		{
			this_thread::sleep_for(std::chrono::microseconds(1000));
			while (!pcTaskQ->Empty())
			{
				this_thread::sleep_for(std::chrono::microseconds(100));
				cout << "Front " << pcTaskQ->Front() << '\n';
				pcTaskQ->Pop();
			}
		}
	);

	th1.join();
	th2.join();

	return 0;
}
