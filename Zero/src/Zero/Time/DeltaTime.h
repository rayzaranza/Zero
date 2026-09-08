#pragma once

namespace Zero
{
    class DeltaTime
    {
      public:
        DeltaTime(float time = 0.0f) : m_Time { time } {}

      public:
        inline float GetSeconds() const { return m_Time; }
        inline float GetMilliseconds() const { return m_Time * 1000.0f; }

      public:
        inline operator float() const { return m_Time; }

      private:
        float m_Time;
    };
}
