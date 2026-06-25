#include "pch.h"
#include "math_dll_c.h"
#include "math_dll.h"
#include <map>
#include <mutex>

std::mutex handle_mutex;
std::map<MathHandle, std::shared_ptr<MathLibrary>> handle_map;

//获取实现对象
std::shared_ptr<MathLibrary> get_impl(MathHandle handle)
{
	std::lock_guard<std::mutex> lock(handle_mutex);
	auto it = handle_map.find(handle);
	if (it != handle_map.end())
	{
		return it->second;
	}
	return nullptr;
}

MATH_HANDLE_API MathHandleErrorCode math_handle_create(MathHandle* handle)
{
	if (handle == nullptr)
	{
		return MATH_HANDLE_ERROR_NULL_PTR;
	}

	auto create = [&]() -> MathHandleErrorCode
		{
			auto impl = std::make_shared<MathLibrary>();
			MathHandle new_handle = static_cast<MathHandle>(impl.get());

			{
				std::lock_guard<std::mutex> lock(handle_mutex);
				handle_map[new_handle] = impl;
			}

			*handle = new_handle;
			return MATH_HANDLE_SUCCESS;
		};

	return create();
}

MATH_HANDLE_API MathHandleErrorCode math_handle_destory(MathHandle handle)
{
	if (handle == nullptr)
	{
		return MATH_HANDLE_SUCCESS;
	}

	auto destroy = [&]() -> MathHandleErrorCode
		{
			std::lock_guard<std::mutex> lock(handle_mutex);
			auto it = handle_map.find(handle);
			if (it != handle_map.end())
			{
				handle_map.erase(it);
				return MATH_HANDLE_SUCCESS;
			}
			return MATH_HANDLE_ERROR_INVALID_HANDLE;
		};

	return destroy();

}

MATH_HANDLE_API MathHandleErrorCode math_handle_add(MathHandle handle, int a, int b, int* result)
{
	if (handle == nullptr)
	{
		return MATH_HANDLE_ERROR_NULL_PTR;
	}

	auto add = [&]() -> MathHandleErrorCode
		{
			auto impl = get_impl(handle);
			if (impl)
			{
				*result = impl->Add(a, b);
				return MATH_HANDLE_SUCCESS;
			}
			return MATH_HANDLE_ERROR_INVALID_HANDLE;
		};

	return add();
}

