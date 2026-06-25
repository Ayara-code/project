#include "pch.h"
#include "math_dll.h"

int MathLibrary::Add(int a, int b)
{
	return a + b;
}

int MathLibrary::Multiply(int a, int b)
{
	return a * b;
}

double MathLibrary::Divide(double a, double b)
{
	if (b == 0) return 0.0;
	return a / b;
}





/*2
* // C风格函数实现
extern "C" {
    MATH_API int AddNumbers(int a, int b) {
        return MathLibrary::Add(a, b);
    }

    MATH_API double DivideNumbers(double a, double b) {
        if (b == 0) return 0.0;
        return a / b;
    }
}
2*/




/*
#include "MathLibrary.h"
#include <map>
#include <mutex> // 引入互斥锁，确保多线程安全

// C++ 类的内部实现
int MathLibrary::Add(int a, int b) {
    num += (a + b);
    return num;
}

// --- DLL 内部的管理机制（对外隐藏） ---
namespace {
    std::map<int, MathLibrary*> g_InstanceMap; // 句柄到对象指针的映射表
    int g_NextHandle = 1;                     // 自增的句柄计数器
    std::mutex g_MapMutex;                    // 保证多线程操作 map 时的安全
}

// 1. 创建对象，分配句柄
int CreateMathHandle() {
    std::lock_guard<std::mutex> lock(g_MapMutex);

    MathLibrary* instance = new MathLibrary();
    int currentHandle = g_NextHandle++;

    g_InstanceMap[currentHandle] = instance; // 记录映射关系
    return currentHandle;                    // 返回给外部一个数字
}

// 2. 根据句柄找到对象并调用
int AddNumbersByHandle(int handle, int a, int b) {
    std::lock_guard<std::mutex> lock(g_MapMutex);

    // 在 map 中查找该句柄是否存在
    auto it = g_InstanceMap.find(handle);
    if (it != g_InstanceMap.end()) {
        MathLibrary* math = it->second; // 找到了，取出真正的 C++ 对象指针
        return math->Add(a, b);
    }

    return -1; // 找不到句柄，返回错误码
}

// 3. 根据句柄释放内存
void DestroyMathHandle(int handle) {
    std::lock_guard<std::mutex> lock(g_MapMutex);

    auto it = g_InstanceMap.find(handle);
    if (it != g_InstanceMap.end()) {
        delete it->second;          // 释放 C++ 对象内存
        g_InstanceMap.erase(it);    // 从 map 中移除该记录
    }
}
*/