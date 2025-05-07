#define _CRT_SECURE_NO_WARNINGS

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

    // 创建或打开共享内存
    managed_shared_memory shared_memory(open_or_create, "SharedMemory", 1024);

    // 在共享内存中创建一个 SharedData 对象
    SharedData* shared_data = shared_memory.find_or_construct<SharedData>("SharedData")();
    shared_data->data_ready = false;

    // 创建消息队列
    message_queue::remove("MessageQueue");  // 删除现有的消息队列
    message_queue mq(create_only, "MessageQueue", 1, sizeof(bool));

    {
        // 锁定共享内存中的互斥量
        scoped_lock<interprocess_mutex> lock(shared_data->mutex);

        // 写入消息到共享内存
        std::string message = "Hello from Producer!";
        std::strncpy(shared_data->message, message.c_str(), sizeof(shared_data->message));

        // 标记数据准备好了
        shared_data->data_ready = true;

        // 通知消费者数据已经准备好
        shared_data->condition.notify_one();
    }

    // 发送消息到消息队列通知消费者
    bool notify = true;
    mq.send(&notify, sizeof(notify), 0);

    std::cout << "Producer sent: " << shared_data->message << std::endl;

    system("pause");

    return 0;
}
