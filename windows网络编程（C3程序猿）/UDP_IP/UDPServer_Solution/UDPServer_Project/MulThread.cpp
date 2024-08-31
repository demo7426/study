//#include <iostream>
//#include <vector>
//#include <queue>
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//#include <functional>
//
//class ThreadPool {
//public:
//    ThreadPool(size_t numThreads) : stop(false) {
//        for (size_t i = 0; i < numThreads; ++i) {
//            workers.emplace_back(
//                [this] {
//                    while (true) {
//                        std::function<void()> task;
//
//                        {
//                            std::unique_lock<std::mutex> lock(queueMutex);
//                            condition.wait(lock, [this] { return stop || !tasks.empty(); });
//
//                            if (stop && tasks.empty()) {
//                                return;
//                            }
//
//                            task = std::move(tasks.front());
//                            tasks.pop();
//
//                            task();
//                        }
//
//                        
//                    }
//                }
//            );
//        }
//    }
//
//    template<class F, class... Args>
//    void enqueue(F&& f, Args&&... args) {
//        {
//            std::unique_lock<std::mutex> lock(queueMutex);
//            auto task = std::make_shared<std::function<void()>>([=]() { std::invoke(f, args...); });
//            tasks.emplace([task]() { (*task)(); });
//        }
//        condition.notify_one();
//    }
//
//
//
//    ~ThreadPool() {
//        {
//            std::unique_lock<std::mutex> lock(queueMutex);
//            stop = true;
//        }
//        condition.notify_all();
//        for (std::thread& worker : workers) {
//            worker.join();
//        }
//    }
//
//private:
//    std::vector<std::thread> workers;
//    std::queue<std::function<void()>> tasks;
//    std::mutex queueMutex;
//    std::condition_variable condition;
//    bool stop;
//};
//
//// 使用示例
//void taskFunction(int num) {
//    std::cout << "Task " << num << " is running." << std::endl;
//}
//
//int main() {
//    ThreadPool pool(4); // 创建一个拥有4个线程的线程池
//
//    // 加入任务到线程池
//    for (int i = 0; i < 8; ++i) {
//        pool.enqueue(taskFunction, i);
//    }
//
//    return 0;
//}
