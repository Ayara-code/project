#pragma once

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else 
#define EXTERN_C 
#endif 


// 导出宏定义
#ifdef MATHDLL_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif

class MATH_API MathLibrary
{
public:
	static int Add(int a, int b);
	static int Multiply(int a, int b);
	static double Divide(double a, double b);
};


// 导出C风格函数
//extern "C"
//{
//	MATH_API int AddNumbers(int a, int b);
//	MATH_API double DivideNumbers(double a, double b);
//}


/*2
EXTERN_C MATH_API int AddNumbers(int a, int b);
EXTERN_C MATH_API double DivideNumbers(double a, double b);
2*/


// 增加句柄
/*
* 
#pragma once

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif

#ifdef MATHDLL_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif

// 正常的 C++ 类定义
class MATH_API MathLibrary
{
private:
	int num = 0;
public:
	int Add(int a, int b);
};

// --- 基于句柄（Handle）的 C 接口 ---

// 创建对象，返回一个整数句柄（代表这个对象）
EXTERN_C MATH_API int CreateMathHandle();

// 传入句柄、参数，执行操作
EXTERN_C MATH_API int AddNumbersByHandle(int handle, int a, int b);

// 传入句柄，销毁对应的对象
EXTERN_C MATH_API void DestroyMathHandle(int handle);
*/