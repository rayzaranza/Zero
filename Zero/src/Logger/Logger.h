#pragma once
#include "Zero/Core.h"
#include <memory>
#include <spdlog/spdlog.h>

namespace Zero
{
    using LoggerPointer = std::shared_ptr<spdlog::logger>;

    class ZERO_API Logger
    {
    private:
        static LoggerPointer s_CoreLogger;
        static LoggerPointer s_ClientLogger;

    public:
        static void Init();
        static LoggerPointer& GetCoreLogger();
        static LoggerPointer& GetClientLogger();
    };
}

#define ZR_CORE_LOG(...)            ::Zero::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define ZR_CORE_LOG_INFO(...)       ::Zero::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define ZR_CORE_LOG_ERROR(...)      ::Zero::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define ZR_CORE_LOG_WARN(...)       ::Zero::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define ZR_CORE_LOG_CRITICAL(...)   ::Zero::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define ZR_LOG(...)                 ::Zero::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define ZR_LOG_INFO(...)            ::Zero::Logger::GetClientLogger()->info(__VA_ARGS__)
#define ZR_LOG_ERROR(...)           ::Zero::Logger::GetClientLogger()->error(__VA_ARGS__)
#define ZR_LOG_WARN(...)            ::Zero::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define ZR_LOG_CRITICAL(...)        ::Zero::Logger::GetClientLogger()->critical(__VA_ARGS__)
