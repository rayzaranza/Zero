#include "KeyEvent.h"

namespace Zero
{
    // ················································································································
    //  Key Event
    // ················································································································
    KeyEvent::KeyEvent(int keyCode) : m_KeyCode { keyCode }
    {}

    int KeyEvent::GetKeyCode() const
    {
        return m_KeyCode;
    }

    int KeyEvent::GetCategoryFlags() const
    {
        return EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput;
    }

    // ················································································································
    //  Key Pressed Event
    // ················································································································
    KeyPressedEvent::KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent { keyCode }, m_RepeatCount { repeatCount }
    {}

    int KeyPressedEvent::GetRepeatCount() const
    {
        return m_RepeatCount;
    }

    std::string KeyPressedEvent::ToString() const
    {
        std::stringstream stream {};
        stream << "KeyPressedEvent: " << m_KeyCode << " (repeats: " << m_RepeatCount << ")";
        return stream.str();
    }

    EventType KeyPressedEvent::GetStaticType()
    {
        return EventType::KeyPressed;
    }

    EventType KeyPressedEvent::GetEventType() const
    {
        return GetStaticType();
    }

    const char* KeyPressedEvent::GetName() const
    {
        return "KeyPressed";
    }

    // ················································································································
    // Key Released Event
    // ················································································································
    KeyReleasedEvent::KeyReleasedEvent(int keyCode) : KeyEvent { keyCode }
    {}

    std::string KeyReleasedEvent::ToString() const
    {
        std::stringstream stream {};
        stream << "KeyReleasedEvent: " << m_KeyCode;
        return stream.str();
    }

    EventType KeyReleasedEvent::GetStaticType()
    {
        return EventType::KeyReleased;
    }

    EventType KeyReleasedEvent::GetEventType() const
    {
        return GetStaticType();
    }

    const char* KeyReleasedEvent::GetName() const
    {
        return "KeyReleased";
    }

    // ················································································································
    // Key Typed Event
    // ················································································································
    KeyTypedEvent::KeyTypedEvent(int keyCode) : KeyEvent { keyCode }
    {}

    std::string KeyTypedEvent::ToString() const
    {
        std::stringstream stream {};
        stream << "KeyTypedEvent: " << m_KeyCode;
        return stream.str();
    }

    EventType KeyTypedEvent::GetStaticType()
    {
        return EventType::KeyTyped;
    }

    EventType KeyTypedEvent::GetEventType() const
    {
        return GetStaticType();
    }

    const char* KeyTypedEvent::GetName() const
    {
        return "KeyTyped";
    }
}
