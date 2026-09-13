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
        String Name{};
        I64 Start{};
        I64 End{};
        U64 ThreadID{};
    };

    //======================================================================================
    //  Profiler Session
    //======================================================================================
    struct ProfilerSession
    {
        String Name{};
    };

    //======================================================================================
    //  Profiler
    //======================================================================================
    class Profiler
    {
      public:
        Profiler();

      public:
        void BeginSession(const String& name, const String& filePath = "results.json");
        void EndSession();
        void WriteProfile(const ProfileResult& result);
        void WriteHeader();
        void WriteFooter();

      public:
        static Profiler& Get();

      private:
        ProfilerSession* m_CurrentSession;
        std::ofstream m_OutputStream{};
        I32 m_ProfileCount;
    };

    //======================================================================================
    //  Profiler Timer
    //======================================================================================
    class ProfilerTimer
    {
      private:
        using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

      public:
        ProfilerTimer(const String& name) : m_Name{ name }, m_IsStopped{ false }, m_StartTime{ std::chrono::high_resolution_clock::now() } {}

        ~ProfilerTimer()
        {
            if (!m_IsStopped)
                Stop();
        }

      public:
        void Stop()
        {
            const TimePoint endTime{ std::chrono::high_resolution_clock::now() };
            const I64 start{ std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count() };
            const I64 end{ std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count() };
            const U64 threadId{ std::hash<std::thread::id>{}(std::this_thread::get_id()) };

            Profiler::Get().WriteProfile({ m_Name, start, end, threadId });
            m_IsStopped = true;
        }

      private:
        String m_Name;
        Boolean m_IsStopped;
        TimePoint m_StartTime;
    };
}

#define ZR_ENABLE_PROFILER 1

#if ZR_ENABLE_PROFILER
#   define ZR_PROFILE_BEGIN_SESSION(name, filePath) ::Zero::Profiler::Get().BeginSession(name, filePath)
#   define ZR_PROFILE_END_SESSION() ::Zero::Profiler::Get().EndSession()
#   define ZR_PROFILE_SCOPE(name) ::Zero::ProfilerTimer timer##__LINE__(name)
#   define ZR_PROFILE_FUNCTION() ZR_PROFILE_SCOPE(__FUNCSIG__)
#else
#   define ZR_PROFILE_BEGIN_SESSION(name)
#   define ZR_PROFILE_END_SESSION()
#   define ZR_PROFILE_SCOPE(name)
#   define ZR_PROFILE_FUNCTION()
#endif
