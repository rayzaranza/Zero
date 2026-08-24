#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> ZY::Logger::logger;

void ZY::Logger::init()
{
	spdlog::set_pattern("%^[%T]: %v%$");
	logger = spdlog::stdout_color_mt("ZY");
	logger->set_level(spdlog::level::trace);
}
