#pragma once
#include<memory>
#include"Core.h"
#include"spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace ZJY {
	class ZJY_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log 
#define Z_CORE_ERROR(...)   ::ZJY::Log::GetCoreLogger()->error(__VA_ARGS__)
#define Z_CORE_WARN(...)    ::ZJY::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define Z_CORE_INFO(...)    ::ZJY::Log::GetCoreLogger()->info(__VA_ARGS__)
#define Z_CORE_TRACE(...)   ::ZJY::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define Z_CORE_FATAL(...)   ::ZJY::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log 
#define Z_CLIENT_ERROR(...)  ::ZJY::Log::GetClientLogger()->error(__VA_ARGS__)
#define Z_CLIENT_WARN(...)   ::ZJY::Log::GetClientLogger()->warn(__VA_ARGS__)
#define Z_CLIENT_INFO(...)   ::ZJY::Log::GetClientLogger()->info(__VA_ARGS__)
#define Z_CLIENT_TRACE(...)  ::ZJY::Log::GetClientLogger()->trace(__VA_ARGS__)
#define Z_CLIENT_FATAL(...)  ::ZJY::Log::GetClientLogger()->fatal(__VA_ARGS__)

