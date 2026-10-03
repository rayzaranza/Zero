#pragma once


namespace Zero {


class DeltaTime
{
  public:
    DeltaTime(const float time = 0.0f);

  public:
    float GetSeconds() const;
    float GetMilliseconds() const;
    operator float() const;

  private:
    float m_Time;
};


}
