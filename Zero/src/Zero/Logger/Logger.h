#pragma once

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include "Zero/Core.h"

namespace Zero
{
    class Logger
    {
      private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;

      public:
        static void Initialize();
        inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };
    };
}

#define ZR_CORE_LOG(...) ::Zero::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define ZR_CORE_INFO(...) ::Zero::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define ZR_CORE_ERROR(...) ::Zero::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define ZR_CORE_WARN(...) ::Zero::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define ZR_CORE_CRITICAL(...) ::Zero::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define ZR_LOG(...) ::Zero::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define ZR_INFO(...) ::Zero::Logger::GetClientLogger()->info(__VA_ARGS__)
#define ZR_ERROR(...) ::Zero::Logger::GetClientLogger()->error(__VA_ARGS__)
#define ZR_WARN(...) ::Zero::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define ZR_CRITICAL(...) ::Zero::Logger::GetClientLogger()->critical(__VA_ARGS__)
