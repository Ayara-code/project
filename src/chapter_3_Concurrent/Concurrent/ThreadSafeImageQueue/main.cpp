#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "ThreadSafeImageQueue.h" // 确保你的头文件叫这个名字

// 模拟一个图像结构体，避免引入复杂的 OpenCV 库
struct MockImage {
    int frame_id;
    std::string timestamp;
};

// 生产者线程函数
void producer_task(ThreadSafeImageQueue<MockImage>& queue) {
    for (int i = 1; i <= 10; ++i) {
        MockImage img{ i, "2026-06-24 23:59:00" };

        std::cout << "[生产者] 准备推入帧 #" << img.frame_id << "..." << std::endl;

        // 尝试推入队列，设置超时时间为 100 毫秒
        if (queue.push(img, 100)) {
            std::cout << "[生产者] 成功推入帧 #" << img.frame_id
                << " (当前队列大小: " << queue.size() << ")" << std::endl;
        }
        else {
            std::cout << "[生产者]  推入帧 #" << img.frame_id << " 失败（超时或队列关闭）" << std::endl;
        }

        // 模拟摄像头 30ms 抓取一帧
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    std::cout << "[生产者] 图像抓取完毕，正在关闭队列..." << std::endl;
    queue.shutdown(); // 生产结束，关闭队列，通知消费者别等了
}

// 消费者线程函数
void consumer_task(ThreadSafeImageQueue<MockImage>& queue) {
    while (true) {
        MockImage img;

        // 消费者尝试从队列取图，设置超时时间为 1000 毫秒
        // 如果队列被 shut_down 且队列空了，pop 会立刻返回 false
        if (queue.pop(img, 1000)) {
            std::cout << "\t[消费者]  成功取出帧 #" << img.frame_id
                << "，开始处理..." << std::endl;

            // 模拟图像处理耗时（50ms），故意比生产者慢，测试队列满时的阻塞情况
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            std::cout << "\t[消费者] 帧 #" << img.frame_id << " 处理完成。" << std::endl;
        }
        else {
            // 如果 pop 返回 false，说明队列空了且已经 shut_down，或者等了 1 秒都没数据
            std::cout << "\t[消费者]  停止接收（队列已空且关闭，或等待超时）" << std::endl;
            break;
        }
    }
}

int main() {

    // 创建一个容量最大为 3 的图像队列
    // 容量设小一点（比如 3），可以完美观察到“队列满了之后生产者被阻塞”的现象
    ThreadSafeImageQueue<MockImage> image_queue(3);

    std::cout << "=== SPSC 图像队列测试开始 ===" << std::endl;

    // 启动生产者和消费者线程
    std::thread producer(producer_task, std::ref(image_queue));
    std::thread consumer(consumer_task, std::ref(image_queue));

    // 等待两个线程执行完毕
    if (producer.joinable()) producer.join();
    if (consumer.joinable()) consumer.join();

    std::cout << "=== SPSC 图像队列测试结束 ===" << std::endl;
    return 0;
}