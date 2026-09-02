#include "MouseEvent.h"

namespace Zero
{
    // ················································································································
    //  Mouse Moved Event
    // ················································································································
    MouseMovedEvent::MouseMovedEvent(float x, float y) : m_MouseX { x }, m_MouseY { y }
    {
    }

    inline float MouseMovedEvent::GetX() const
    {
        return m_MouseX;
    }

    inline float MouseMovedEvent::GetYOffset() const
    {
        return m_MouseY;
    }

    std::string MouseMovedEvent::ToString() const
    {
        std::stringstream stream {};
        stream << "MouseMovementEvent: " << m_MouseX << ", " << m_MouseY;
        return stream.str();
    }

    EventType MouseMovedEvent::GetStaticType()
    {
        return EventType::MouseMoved;
    }

    EventType MouseMovedEvent::GetEventType() const
    {
        return GetStaticType();
    }

    const char* MouseMovedEvent::GetName() const
    {
        return "MouseMoved";
    }

    int MouseMovedEvent::GetCategoryFlags() const
    {
        return EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput;
    }

    // ················································································································
    //  Mouse Scrolled Event
    // ················································································································
    MouseScrolledEvent::MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset { xOffset }, m_YOffset { yOffset }
    {
    }

    inline float MouseScrolledEvent::GetXOffset() const
    {
        return m_XOffset;
    }

    inline float MouseScrolledEvent::GetYOffset() const
    {
        return m_YOffset;
    }

    std::string MouseScrolledEvent::ToString() const
    {
        std::stringstream stream {};
        stream << "MouseMovementEvent: " << m_XOffset << ", " << m_YOffset;
        return stream.str();
    }

    EventType MouseScrolledEvent::GetStaticType()
    {
        return EventType::MouseScrolled;
    }

    EventType MouseScrolledEvent::GetEventType() const
    {
        return GetStaticType();
    }

    const char* MouseScrolledEvent::GetName() const
    {
        return "MouseScrolled";
    }

    int MouseScrolledEvent::GetCategoryFlags() const
    {
        return EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput;
    }

    // ················································································································
    //  Mouse Button Event
    // ················································································································
    MouseButtonEvent::MouseButtonEvent(int button) : m_Button { button }
    {
    }

    inline int MouseButtonEvent::GetMouseButton() const
    {
        return m_Button;
    }

    int MouseButtonEvent::GetCategoryFlags() const
    {
        return EventCategory::EventCategoryMouseButton | EventCategory::EventCategoryInput;
    }

    // ················································································································
    // Mouse Button Pressed Event
    // ················································································································
    MouseButtonPressedEvent::MouseButtonPressedEvent(int button) : MouseButtonEvent { button }
    {
    }

    std::string MouseButtonPressedEvent::ToString() const
    {
        std::stringstream stream {};
        stream << "MouseButtonPressedEvent: " << m_Button;
        return stream.str();
    }

    EventType MouseButtonPressedEvent::GetStaticType()
    {
        return EventType::MouseButtonPressed;
    }

    EventType MouseButtonPressedEvent::GetEventType() const
    {
        return GetStaticType();
    }

    // ················································································································
    //  Mouse Button Released Event
    // ················································································································
    MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button) : MouseButtonEvent { button }
    {
    }

    std::string MouseButtonReleasedEvent::ToString() const
    {
        std::stringstream stream {};
        stream << "MouseButtonReleasedEvent: " << m_Button;
        return stream.str();
    }

    EventType MouseButtonReleasedEvent::GetStaticType()
    {
        return EventType::MouseButtonReleased;
    }

    EventType MouseButtonReleasedEvent::GetEventType() const
    {
        return GetStaticType();
    }
}
