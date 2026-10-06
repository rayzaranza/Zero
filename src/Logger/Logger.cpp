#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>


namespace Zero {


Ref<spdlog::logger> Logger::s_Logger {};


void Logger::Init()
{

    spdlog::set_pattern("%^ %T | %v%$");

    s_Logger = spdlog::stdout_color_mt("Zero");
    s_Logger->set_level(spdlog::level::trace);
}


Ref<spdlog::logger>& Logger::GetLogger()
{
    return s_Logger;
}


}
