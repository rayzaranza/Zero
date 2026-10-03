#include "Zero/Time/DeltaTime.h"


Zero::DeltaTime::DeltaTime(const float time) : m_Time{ time }
{
}


Zero::DeltaTime::operator float() const
{
    return m_Time;
}


float Zero::DeltaTime::GetSeconds() const
{
    return m_Time;
}


float Zero::DeltaTime::GetMilliseconds() const
{
    return m_Time * 1000.0f;
}
