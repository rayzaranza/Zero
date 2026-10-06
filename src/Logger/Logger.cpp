#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>


Zero::Ref<spdlog::logger> Zero::Logger::s_Logger {};


void Zero::Logger::Init()
{
    spdlog::set_pattern("%^ %T | %v%$");

    s_Logger = spdlog::stdout_color_mt("Zero");
    s_Logger->set_level(spdlog::level::trace);
}


Zero::Ref<spdlog::logger>& Zero::Logger::GetLogger()
{
    return s_Logger;
}
