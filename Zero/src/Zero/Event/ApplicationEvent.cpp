#include "ApplicationEvent.h"

namespace Zero
{
    // ················································································································
    //  Window Resized Event
    // ················································································································
    WindowResizedEvent::WindowResizedEvent(unsigned int width, unsigned int height)
        : m_Width { width }, m_Height { height }
    {}

    inline unsigned int WindowResizedEvent::GetWidth() const
    {
        return m_Width;
    }

    inline unsigned int WindowResizedEvent::GetHeight() const
    {
        return m_Height;
    }

    std::string WindowResizedEvent::ToString() const
    {
        std::stringstream stream {};
        stream << GetName() << ": " << m_Width << ", " << m_Height;
        return stream.str();
    }

    EventType WindowResizedEvent::GetStaticType()
    {
        return EventType::WindowResized;
    }

    EventType WindowResizedEvent::GetEventType() const
    {
        return GetStaticType();
    }

    const char* WindowResizedEvent::GetName() const
    {
        return "WindowResized";
    }

    int WindowResizedEvent::GetCategoryFlags() const
    {
        return EventCategory::EventCategoryApplication;
    }

    // ················································································································
    //  Window Closed Event
    // ················································································································
    std::string WindowClosedEvent::ToString() const
    {
        return GetName();
    }

    EventType WindowClosedEvent::GetStaticType()
    {
        return EventType::WindowClosed;
    }

    EventType WindowClosedEvent::GetEventType() const
    {
        return GetStaticType();
    }

    const char* WindowClosedEvent::GetName() const
    {
        return "WindowClosed";
    }

    int WindowClosedEvent::GetCategoryFlags() const
    {
        return EventCategory::EventCategoryApplication;
    }

    // ················································································································
    //  Application Ticked Event
    // ················································································································
    std::string ApplicationTickedEvent::ToString() const
    {
        return GetName();
    }

    EventType ApplicationTickedEvent::GetStaticType()
    {
        return EventType::ApplicationTicked;
    }

    EventType ApplicationTickedEvent::GetEventType() const
    {
        return GetStaticType();
    }

    const char* ApplicationTickedEvent::GetName() const
    {
        return "ApplicationTicked";
    }

    int ApplicationTickedEvent::GetCategoryFlags() const
    {
        return EventCategory::EventCategoryApplication;
    }

    // ················································································································
    //  Application Updated Event
    // ················································································································
    std::string ApplicationUpdatedEvent::ToString() const
    {
        return GetName();
    }

    EventType ApplicationUpdatedEvent::GetStaticType()
    {
        return EventType::ApplicationUpdated;
    }

    EventType ApplicationUpdatedEvent::GetEventType() const
    {
        return GetStaticType();
    }

    const char* ApplicationUpdatedEvent::GetName() const
    {
        return "ApplicationTicked";
    }

    int ApplicationUpdatedEvent::GetCategoryFlags() const
    {
        return EventCategory::EventCategoryApplication;
    }

    // ················································································································
    //  Application Rendered Event
    // ················································································································
    std::string ApplicationRenderedEvent::ToString() const
    {
        return GetName();
    }

    EventType ApplicationRenderedEvent::GetStaticType()
    {
        return EventType::ApplicationRendered;
    }

    EventType ApplicationRenderedEvent::GetEventType() const
    {
        return GetStaticType();
    }

    const char* ApplicationRenderedEvent::GetName() const
    {
        return "ApplicationRendered";
    }

    int ApplicationRenderedEvent::GetCategoryFlags() const
    {
        return EventCategory::EventCategoryApplication;
    }
}
