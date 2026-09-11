#pragma once

#include "Zero/Core.h"
#include "Zero/Event/Event.h"

namespace Zero
{
    //======================================================================================
    //  Window Resized Event
    //======================================================================================
    class WindowResizedEvent : public Event
    {
      public:
        WindowResizedEvent(I32 width, I32 height) : m_Width{ width }, m_Height{ height } {}

      public:
        inline I32 GetWidth() const { return m_Width; }
        inline I32 GetHeight() const { return m_Height; }
        inline static EventType GetStaticType() { return EventType::WindowResized; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "WindowResized"; }
        inline virtual I32 GetCategoryFlags() const override { return EventCategoryApplication; }
        inline virtual String ToString() const override
        {
            std::stringstream stream{};
            stream << GetName() << ": " << m_Width << ", " << m_Height;
            return stream.str();
        }

      private:
        I32 m_Width;
        I32 m_Height;
    };

    //======================================================================================
    //  Window Closed Event
    //======================================================================================
    class WindowClosedEvent : public Event
    {
      public:
        WindowClosedEvent() = default;

      public:
        inline static EventType GetStaticType() { return EventType::WindowClosed; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "WindowClosed"; }
        inline virtual I32 GetCategoryFlags() const override { return EventCategoryApplication; }
        inline virtual String ToString() const override { return GetName(); }
    };

    //======================================================================================
    //  Application Ticked Event
    //======================================================================================
    class ApplicationTickedEvent : public Event
    {
      public:
        ApplicationTickedEvent() = default;

      public:
        inline static EventType GetStaticType() { return EventType::ApplicationTicked; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "ApplicationTicked"; }
        inline virtual I32 GetCategoryFlags() const override { return EventCategoryApplication; }
        inline virtual String ToString() const override { return GetName(); }
    };

    //======================================================================================
    //  Application Updated Event
    //======================================================================================
    class ApplicationUpdatedEvent : public Event
    {
      public:
        ApplicationUpdatedEvent() = default;

      public:
        inline static EventType GetStaticType() { return EventType::ApplicationUpdated; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "ApplicationUpdated"; }
        inline virtual I32 GetCategoryFlags() const override { return EventCategoryApplication; }
        inline virtual String ToString() const override { return GetName(); }
    };

    //======================================================================================
    //  Application Rendered Event
    //======================================================================================
    class ApplicationRenderedEvent : public Event
    {
      public:
        ApplicationRenderedEvent() = default;

      public:
        inline static EventType GetStaticType() { return EventType::ApplicationRendered; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "ApplicationRendered"; }
        inline virtual I32 GetCategoryFlags() const override { return EventCategoryApplication; }
        inline virtual String ToString() const override { return GetName(); }
    };
}
