#pragma once
#include "Zero/Core/Core.h"

namespace Zero {
  enum class EventType : uint8_t {
    None,
    WindowClosed,
    WindowResized,
    WindowFocused,
    WindowLostFocus,
    WindowMoved,
    ApplicationTicked,
    ApplicationUpdated,
    ApplicationRendered,
    KeyPressed,
    KeyReleased,
    KeyTyped,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
  };

  enum EventCategory : uint8_t {
    None,
    EventCategoryApplication = 1 << 0,
    EventCategoryInput = 1 << 1,
    EventCategoryKeyboard = 1 << 2,
    EventCategoryMouse = 1 << 3,
    EventCategoryMouseButton = 1 << 4,
  };

  class Event {
  public:
    virtual ~Event() = default;
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int32_t GetCategoryFlags() const = 0;
    virtual std::string ToString() const;
    bool IsHandled() const;
    bool IsInCategory(EventCategory category) const;

  protected:
    bool m_IsHandled{ false };
    friend class EventDispatcher;
  };

  class EventDispatcher {
  public:
    EventDispatcher(Event& event);

    template <typename T>
    bool Dispatch(Function<bool(T&)> function) {
      if (m_Event.GetEventType() == T::GetStaticType()) {
        m_Event.m_IsHandled = function(*(T*)&m_Event);
        return true;
      }
      return false;
    }

  private:
    Event& m_Event;
  };
}

std::ostream& operator<<(std::ostream& stream, const Zero::Event& event);

template <> struct fmt::formatter<Zero::Event> : fmt::ostream_formatter {};
