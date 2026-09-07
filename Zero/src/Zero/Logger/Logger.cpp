#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Zero
{
    LoggerPointer Logger::s_CoreLogger;
    LoggerPointer Logger::s_ClientLogger;

    void Logger::Init()
    {
        spdlog::set_pattern("%^ %T | %n | %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("ZERO");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP ");
        s_ClientLogger->set_level(spdlog::level::trace);
    }

    LoggerPointer& Logger::GetCoreLogger()
    {
        return s_CoreLogger;
    }

    LoggerPointer& Logger::GetClientLogger()
    {
        return s_ClientLogger;
    }
}
