// Thread.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>

void hello_thread()
{
    std::cout << "Hello from thread! Thread ID: "
        << std::this_thread::get_id() << std::endl;

}

void worker_thread(int iterations)
{
    for (int i = 0; i < iterations; ++i)
    {
        std::cout << "Worker iteration:" << i
            << " Thread ID: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

class ThreadManager {
public:
    // 1. 使用普通函数
    static void static_function(int id) {
        std::cout << "Static function, thread " << id << std::endl;
    }

    // 2. 使用成员函数
    void member_function(int id) {
        std::cout << "Member function, thread " << id
            << " this: " << this << std::endl;
    }
};

// 4. 使用函数对象,重载小括号运算符
struct Functor {
    void operator()(int id) const {
        std::cout << "Functor, thread " << id << std::endl;
    }
};

int main()
{
    ThreadManager manager;
    ThreadManager manager2;

    //方式1 静态函数
    std::thread t1(ThreadManager::static_function, 1);

    //方式2 成员函数
    std::thread t2(&ThreadManager::member_function, &manager, 2);

    //方式3 lambda表达式
    std::thread t3([](int id)
        {
            std::cout << "Inline lambda, thread " << id << std::endl;
        }, 3);

    //方式4 函数对象
    std::thread t4(Functor(), 4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

   // std::thread t2(worker_thread, 5);
   // t2.join();
   //  std::cout << "Hello World!\n";
   //  std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
