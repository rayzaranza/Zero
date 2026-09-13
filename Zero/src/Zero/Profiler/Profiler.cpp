#include "Zero/Profiler/Profiler.h"

namespace Zero
{
    Profiler::Profiler() : m_CurrentSession{ nullptr }, m_ProfileCount{ 0 }
    {}

    void Profiler::BeginSession(const String& name, const String& filePath)
    {
        m_OutputStream.open(filePath);
        WriteHeader();
        m_CurrentSession = new ProfilerSession{ name };
    }

    void Profiler::EndSession()
    {
        WriteFooter();
        m_OutputStream.close();
        delete m_CurrentSession;
        m_CurrentSession = nullptr;
        m_ProfileCount = 0;
    }

    void Profiler::WriteProfile(const ProfileResult& result)
    {
        if (m_ProfileCount++ > 0)
            m_OutputStream << ",";

        String name{ result.Name };
        std::replace(name.begin(), name.end(), '"', '\'');

        m_OutputStream << "{";
        m_OutputStream << "\"cat\":\"function\", ";
        m_OutputStream << "\"dur\":" << (result.End - result.Start) << ", ";
        m_OutputStream << "\"name\":\"" << name << "\", ";
        m_OutputStream << "\"ph\":\"X\", ";
        m_OutputStream << "\"pid\":0, ";
        m_OutputStream << "\"tid\":" << result.ThreadID << ", ";
        m_OutputStream << "\"ts\":" << result.Start;
        m_OutputStream << "}";

        m_OutputStream.flush();
    }

    void Profiler::WriteHeader()
    {
        m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        m_OutputStream.flush();
    }

    void Profiler::WriteFooter()
    {
        m_OutputStream << "]}";
        m_OutputStream.flush();
    }

    Profiler& Profiler::Get()
    {
        static Profiler* instance{ new Profiler() };
        return *instance;
    }
}
