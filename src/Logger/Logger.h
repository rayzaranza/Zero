#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace ZY
{
	class Logger
	{
	public:
		static void init();
		static std::shared_ptr<spdlog::logger> logger;
	};
}

#define LOG(...) ::ZY::Logger::logger->trace(__VA_ARGS__)
#define LOG_INFO(...) ::ZY::Logger::logger->info(__VA_ARGS__)
#define LOG_ERROR(...) ::ZY::Logger::logger->error(__VA_ARGS__)
#define LOG_WARN(...) ::ZY::Logger::logger->warn(__VA_ARGS__)
#define LOG_CRITICAL(...) ::ZY::Logger::logger->critical(__VA_ARGS__)