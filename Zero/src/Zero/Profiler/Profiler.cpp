#include "Profiler.h"


Zero::Profiler::Profiler() : m_CurrentSession{ nullptr }, m_ProfileCount{ 0 } {
}


void Zero::Profiler::BeginSession(const std::string& name, const std::string& filePath) {
  m_OutputStream.open(filePath);
  WriteHeader();
  m_CurrentSession = new ProfilerSession{ name };
}


void Zero::Profiler::EndSession() {
  WriteFooter();
  m_OutputStream.close();
  delete m_CurrentSession;
  m_CurrentSession = nullptr;
  m_ProfileCount = 0;
}


void Zero::Profiler::WriteProfile(const ProfileResult& result) {
  if (m_ProfileCount++ > 0) m_OutputStream << ",";

  std::string name{ result.Name };
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


void Zero::Profiler::WriteHeader() {
  m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
  m_OutputStream.flush();
}


void Zero::Profiler::WriteFooter() {
  m_OutputStream << "]}";
  m_OutputStream.flush();
}


Zero::Profiler& Zero::Profiler::Get() {
  static Profiler* instance{ new Profiler() };
  return *instance;
}


Zero::ProfilerTimer::ProfilerTimer(const std::string& name)
  : m_Name{ name }
  , m_IsStopped{ false }
  , m_StartTime{ std::chrono::high_resolution_clock::now() } {
}


Zero::ProfilerTimer::~ProfilerTimer() {
  if (!m_IsStopped) {
    Stop();
  }
}


void Zero::ProfilerTimer::Stop() {
  const TimePoint endTime{ std::chrono::high_resolution_clock::now() };
  const int64_t start{
    std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count()
  };
  const int64_t end{ std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count() };
  const uint64_t threadId{ std::hash<std::thread::id>{}(std::this_thread::get_id()) };
  Profiler::Get().WriteProfile({ m_Name, start, end, threadId });
  m_IsStopped = true;
}


