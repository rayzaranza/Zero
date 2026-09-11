#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Zero
{
    Ref<spdlog::logger> Logger::s_CoreLogger{};
    Ref<spdlog::logger> Logger::s_ClientLogger{};

    void Logger::Initialize()
    {
        spdlog::set_pattern("%^ %T | %n | %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("ZERO");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP ");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}
