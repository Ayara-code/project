// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable condition_;
bool ready = false;

void waiting_thread() {
    std::unique_lock<std::mutex> lock(mtx);  // 1. 获取锁

    // cv.wait() 的内部操作：
    condition_.wait(lock, [] { return ready; });
    // 等效于：
    // while (!ready) {
    //     lock.unlock();       // 2. 暂时释放锁，// ⚠️ lock_guard 没有这个方法
    //     // 进入等待队列（操作系统级）
    //	   internal_wait();
    //     lock.lock();         // 3. 被唤醒后重新获取锁// ⚠️ lock_guard 没有这个方法
    // }

    std::cout << "waiting_thread! Thread ID: "
        << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void trigger_thread() {
    std::unique_lock<std::mutex> lock(mtx);  // 1. 获取锁
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ready = true;
    condition_.notify_all();
    std::cout << "trigger_thread! Thread ID: "
        << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::thread waitingthread(waiting_thread);  //等待线程
    std::thread triggerthread(trigger_thread);  //触发线程

    waitingthread.join();
    triggerthread.join();
    std::cout << "Hello World!\n";
}