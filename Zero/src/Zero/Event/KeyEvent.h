#pragma once
#include "Event.h"
#include "Zero/Input/KeyCode.h"

namespace Zero {
  class KeyEvent : public Event {
  public:
    KeyCode GetKeyCode() const;
    virtual int32_t GetCategoryFlags() const override;

  protected:
    KeyEvent(const KeyCode keyCode);
    KeyCode m_KeyCode{};
  };

  class KeyPressedEvent : public KeyEvent {
  public:
    KeyPressedEvent(const KeyCode keyCode, const int32_t repeatCount);
    int32_t GetRepeatCount() const;
    static EventType GetStaticType();
    virtual EventType GetEventType() const override;
    virtual const char* GetName() const override;
    virtual std::string ToString() const override;

  private:
    int32_t m_RepeatCount;
  };

  class KeyReleasedEvent : public KeyEvent {
  public:
    KeyReleasedEvent(const KeyCode keyCode);
    static EventType GetStaticType();
    virtual EventType GetEventType() const override;
    virtual const char* GetName() const override;
    virtual std::string ToString() const override;
  };

  class KeyTypedEvent : public KeyEvent {
  public:
    KeyTypedEvent(const KeyCode keyCode);
    static EventType GetStaticType();
    virtual EventType GetEventType() const override;
    virtual const char* GetName() const override;
    virtual std::string ToString() const override;
  };
}
