#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <cstring>

struct SharedData {
    boost::interprocess::interprocess_mutex mutex;
    boost::interprocess::interprocess_condition condition;
    bool data_ready;
    char message[100];
};

int main()
{
    using namespace boost::interprocess;

    // 打开共享内存
    managed_shared_memory shared_memory(open_only, "SharedMemory");

    // 查找共享内存中的 SharedData 对象
    SharedData* shared_data = shared_memory.find<SharedData>("SharedData").first;

    if (!shared_data) {
        std::cerr << "Error: Could not find SharedData in shared memory!" << std::endl;
        return 1;
    }

    // 打开消息队列
    message_queue mq(open_only, "MessageQueue");

    // 等待消息队列中的通知
    bool notify;
    message_queue::size_type recvd_size;
    unsigned int priority;
    mq.receive(&notify, sizeof(notify), recvd_size, priority);

    {
        // 锁定共享内存中的互斥量
        scoped_lock<interprocess_mutex> lock(shared_data->mutex);

        // 等待数据准备好
        while (!shared_data->data_ready) {
            shared_data->condition.wait(lock);
        }

        std::cout << "Consumer received: " << shared_data->message << std::endl;
    }

    system("pause");

    return 0;
}
