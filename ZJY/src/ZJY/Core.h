#pragma once

#include<memory>

#ifdef Z_PLATFORM_WINDOWS
#if HZ_DYNAMIC_LINK
	#ifdef Z_BUILD_DLL
		#define ZJY_API __declspec(dllexport)
	#else
		#define ZJY_API __declspec(dllimport)
	#endif // Z_BUILD_DLL
#else
	#define ZJY_API
#endif
#else
	#error ZJY only support Windows;
#endif // Z_PLATFORM_WINDOWS

#ifdef Z_ENABLE_ASSERTS
	#define Z_ASSERT(x, ...) {if(!(x)){Z_CLIENT_ERROR("ASSERTION Failed: {0}",__VA_ARGS__);__debugbreak();}}
	#define Z_CORE_ASSERT(x, ...) {if(!(x)){Z_CORE_ERROR("ASSERTION Failed: {0}",__VA_ARGS__);__debugbreak();}}
#else
	#define Z_ASSERT(x, ...) 
	#define Z_CORE_ASSERT(x, ...) 
#endif // Z_ENABLE_ASSERTS


#define BIT(x) (1<<x)//定义位字段

#define Z_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)//事件绑定

namespace ZJY
{
	//未来会被asset manager所管理的资源才用重命名的sharede-ptr
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}