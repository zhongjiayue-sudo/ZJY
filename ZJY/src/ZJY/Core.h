#pragma once

#ifdef Z_PLATFORM_WINDOWS
	#ifdef Z_BUILD_DLL
		#define ZJY_API __declspec(dllexport)
	#else
		#define ZJY_API __declspec(dllimport)
	#endif // Z_BUILD_DLL
#else
	#error ZJY only support Windows;
#endif // Z_PLATFORM_WINDOWS
