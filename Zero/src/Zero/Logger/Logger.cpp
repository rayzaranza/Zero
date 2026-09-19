#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

Zero::Ref<spdlog::logger> Zero::Logger::s_CoreLogger{};
Zero::Ref<spdlog::logger> Zero::Logger::s_ClientLogger{};

void Zero::Logger::Initialize() {
  spdlog::set_pattern("%^ %T | %n | %v%$");
  s_CoreLogger = spdlog::stdout_color_mt("ZERO");
  s_CoreLogger->set_level(spdlog::level::trace);
  s_ClientLogger = spdlog::stdout_color_mt("APP ");
  s_ClientLogger->set_level(spdlog::level::trace);
}

Zero::Ref<spdlog::logger>& Zero::Logger::GetCoreLogger() {
  return s_CoreLogger;
}

Zero::Ref<spdlog::logger>& Zero::Logger::GetClientLogger() {
  return s_ClientLogger;
}
