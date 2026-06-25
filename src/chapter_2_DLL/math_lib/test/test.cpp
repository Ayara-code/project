// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "include/math_lib.h"

#pragma comment(lib, "lib/math_lib.lib")

int main()
{
    int res = MathUtils::Add(5, 6);
    std::cout << "MathUtils::Add(5, 6) res : "  << res << std::endl;

    
    std::cout << "Hello World!\n";
}


