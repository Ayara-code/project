#pragma once


#if defined(_WIN32)
#ifdef MATHDLL_EXPORTS
#define MATH_HANDLE_API __declspec(dllexport)
#else
#define MATH_HANDLE_API __declspec(dllimport)
#endif
#else
#ifdef MATHDLL_EXPORTS
#define MATH_HANDLE_API __attribute__((visibility("default")))
#else
#define MATH_HANDLE_API
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void* MathHandle;

typedef enum {
    MATH_HANDLE_SUCCESS = 0,
    MATH_HANDLE_ERROR_NULL_PTR = -1,
    MATH_HANDLE_ERROR_INVALID_HANDLE = -2,
    MATH_HANDLE_ERROR_INVALID_ARG = -3,
    MATH_HANDLE_ERROR_DIVIDE_BY_ZERO = -4,
    MATH_HANDLE_ERROR_OUT_OF_MEMORY = -5,
    MATH_HANDLE_ERROR_INTERNAL = -6
} MathHandleErrorCode;

MATH_HANDLE_API MathHandleErrorCode math_handle_create(MathHandle* handle);
MATH_HANDLE_API MathHandleErrorCode math_handle_destory(MathHandle handle);

MATH_HANDLE_API MathHandleErrorCode math_handle_add(MathHandle handle, int a, int b , int* result);



#ifdef __cplusplus
}
#endif