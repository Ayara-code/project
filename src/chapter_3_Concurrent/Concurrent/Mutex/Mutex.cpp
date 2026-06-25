#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

class safeCounter {
private:
    std::mutex _mutex;
    int _count = 0;

public:
    void increment() {
        //其他操作
        //_mutex.lock();
        {
            std::lock_guard<std::mutex> lock(_mutex);
            // 这里存在数据竞争！
            _count = _count + 1;
        }
        //_mutex.unlock();
        //其他操作
    }

    int get_count() const { return _count; }
};

void demonstrate_data_race() {
    safeCounter counter;
    std::vector<std::thread> threads;

    // 创建10个线程，每个增加计数器1000次
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&counter]() {
            for (int j = 0; j < 1000; ++j) {
                counter.increment();
            }
            });
    }

    for (auto& t : threads) {
        t.join();
    }

    // 结果将永远是10000！
    std::cout << "Final count: " << counter.get_count() << std::endl;
}