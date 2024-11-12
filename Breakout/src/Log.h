#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>



namespace Breakout {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }


	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};


}

#ifndef BK_LOG
	#define BK_LOG
	#define BK_ERROR(...) ::Breakout::Log::GetLogger()->error(__VA_ARGS__)
	#define BK_TRACE(...) ::Breakout::Log::GetLogger()->trace(__VA_ARGS__)
	#define BK_INFO(...)  ::Breakout::Log::GetLogger()->info(__VA_ARGS__)
	#define BK_WARN(...)  ::Breakout::Log::GetLogger()->warn(__VA_ARGS__)
	#define BK_FATAL(...) ::Breakout::Log::GetLogger()->critical(__VA_ARGS__)
#endif