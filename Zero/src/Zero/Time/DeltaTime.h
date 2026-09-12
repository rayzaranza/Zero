#pragma once

namespace Zero
{
    class DeltaTime
    {
      public:
        DeltaTime(const Seconds time = 0.0f) : m_Time{ time } {}

      public:
        inline Seconds GetSeconds() const { return m_Time; }
        inline Milliseconds GetMilliseconds() const { return m_Time * 1000.0f; }

      public:
        inline operator F32() const { return m_Time; }

      private:
        Seconds m_Time;
    };
}
