// SPSC.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mutex_;
std::condition_variable cv_;
bool data_ready_ = false;
int shared_data_ = 0;

void producer() {
    std::cout << "Producer: starting work..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    {
        std::lock_guard<std::mutex> lock(mutex_);
        shared_data_ = 42;
        data_ready_ = true;
        std::cout << "Producer: data prepared, notifying..." << std::endl;
    }

    cv_.notify_one();  // 通知一个等待的线程
}

void consumer() {
    std::cout << "Consumer: waiting for data..." << std::endl;

    std::unique_lock<std::mutex> lock(mutex_);

    // 等待条件满足
    cv_.wait(lock, []() {
        std::cout << "Consumer: checking condition..." << std::endl;
        return data_ready_;
        });

    // 条件满足，处理数据
    std::cout << "Consumer: received data = " << shared_data_ << std::endl;
}

int main()
{
    std::thread consumer_thread(&consumer);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread producer_thread(&producer);

    producer_thread.join();
    consumer_thread.join();

    std::cout << "Hello World!\n";
}

