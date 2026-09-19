#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <string>
#include <thread>

namespace Zero
{
    //======================================================================================
    //  Profile Result
    //======================================================================================
    struct ProfileResult
    {
        std::string Name{};
        int64_t Start{};
        int64_t End{};
        uint64_t ThreadID{};
    };

    //======================================================================================
    //  Profiler Session
    //======================================================================================
    struct ProfilerSession
    {
        std::string Name{};
    };

    //======================================================================================
    //  Profiler
    //======================================================================================
    class Profiler
    {
      public:
        Profiler();

      public:
        void BeginSession(const std::string& name, const std::string& filePath = "results.json");
        void EndSession();
        void WriteProfile(const ProfileResult& result);
        void WriteHeader();
        void WriteFooter();

      public:
        static Profiler& Get();

      private:
        ProfilerSession* m_CurrentSession;
        std::ofstream m_OutputStream{};
        int32_t m_ProfileCount;
    };

    //======================================================================================
    //  Profiler Timer
    //======================================================================================
    class ProfilerTimer
    {
      private:
        using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

      public:
        ProfilerTimer(const std::string& name) : m_Name{ name }, m_IsStopped{ false }, m_StartTime{ std::chrono::high_resolution_clock::now() }
        {}

        ~ProfilerTimer()
        {
            if (!m_IsStopped)
                Stop();
        }

      public:
        void Stop()
        {
            const TimePoint endTime{ std::chrono::high_resolution_clock::now() };
            const int64_t start{ std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count() };
            const int64_t end{ std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count() };
            const uint64_t threadId{ std::hash<std::thread::id>{}(std::this_thread::get_id()) };

            Profiler::Get().WriteProfile({ m_Name, start, end, threadId });
            m_IsStopped = true;
        }

      private:
        std::string m_Name;
        bool m_IsStopped;
        TimePoint m_StartTime;
    };
}

#ifdef ZR_ENABLE_PROFILER
#   define ZR_PROFILE_BEGIN_SESSION(name, filePath) ::Zero::Profiler::Get().BeginSession(name, filePath)
#   define ZR_PROFILE_END_SESSION() ::Zero::Profiler::Get().EndSession()
#   define ZR_PROFILE_SCOPE(name) ::Zero::ProfilerTimer timer##__LINE__(name)
#   define ZR_PROFILE_FUNCTION() ZR_PROFILE_SCOPE(__FUNCSIG__)
#else
#   define ZR_PROFILE_BEGIN_SESSION(name, filePath)
#   define ZR_PROFILE_END_SESSION()
#   define ZR_PROFILE_SCOPE(name)
#   define ZR_PROFILE_FUNCTION()
#endif
