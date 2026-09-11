#pragma once

namespace Zero
{
    class DeltaTime
    {
      public:
        DeltaTime(F32 time = 0.0f) : m_Time{ time } {}

      public:
        inline F32 GetSeconds() const { return m_Time; }
        inline F32 GetMilliseconds() const { return m_Time * 1000.0f; }

      public:
        inline operator F32() const { return m_Time; }

      private:
        F32 m_Time;
    };
}
