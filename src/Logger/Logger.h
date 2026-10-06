#pragma once
#include <spdlog/spdlog.h>
#include "../Core/Types.h"


namespace Zero {


class Logger
{
  public:
    static void Init();
    static Ref<spdlog::logger>& GetLogger();

  private:
    static Ref<spdlog::logger> s_Logger;
};


}


#define Z_LOG(...) ::Zero::Logger::GetLogger()->trace(__VA_ARGS__)
#define Z_LOG_ERROR(...) ::Zero::Logger::GetLogger()->error(__VA_ARGS__)
#define Z_LOG_WARN(...) ::Zero::Logger::GetLogger()->warn(__VA_ARGS__)
#define Z_LOG_CRITICAL(...) ::Zero::Logger::GetLogger()->critical(__VA_ARGS__)
#define Z_LOG_INFO(...) ::Zero::Logger::GetLogger()->info(__VA_ARGS__)
