#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Breakout {

	std::shared_ptr<spdlog::logger> Log::s_Logger;


	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		Log::s_Logger = spdlog::stdout_color_mt("Breakout");
		Log::s_Logger->set_level(spdlog::level::trace);
	}
}
