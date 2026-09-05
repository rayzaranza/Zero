#pragma once

#include "Event.h"
#include "Zero/Core.h"

namespace Zero
{
    // ················································································································
    //  Window Resized Event
    // ················································································································
    class WindowResizedEvent : public Event
    {
      public:
        WindowResizedEvent(unsigned int width, unsigned int height);

      public:
        inline unsigned int GetWidth() const;
        inline unsigned int GetHeight() const;

        std::string ToString() const override;

        static EventType GetStaticType();
        virtual EventType GetEventType() const override;
        virtual const char* GetName() const override;
        virtual int GetCategoryFlags() const override;

      private:
        unsigned int m_Width;
        unsigned int m_Height;
    };

    // ················································································································
    //  Window Closed Event
    // ················································································································
    class WindowClosedEvent : public Event
    {
      public:
        WindowClosedEvent() = default;

      public:
        std::string ToString() const override;
        static EventType GetStaticType();
        virtual EventType GetEventType() const override;
        virtual const char* GetName() const override;
        virtual int GetCategoryFlags() const override;
    };

    // ················································································································
    //  Application Ticked Event
    // ················································································································
    class ApplicationTickedEvent : public Event
    {
      public:
        ApplicationTickedEvent() = default;

      public:
        std::string ToString() const override;
        static EventType GetStaticType();
        virtual EventType GetEventType() const override;
        virtual const char* GetName() const override;
        virtual int GetCategoryFlags() const override;
    };

    // ················································································································
    //  Application Updated Event
    // ················································································································
    class ApplicationUpdatedEvent : public Event
    {
      public:
        ApplicationUpdatedEvent() = default;

      public:
        std::string ToString() const override;
        static EventType GetStaticType();
        virtual EventType GetEventType() const override;
        virtual const char* GetName() const override;
        virtual int GetCategoryFlags() const override;
    };

    // ················································································································
    //  Application Rendered Event
    // ················································································································
    class ApplicationRenderedEvent : public Event
    {
      public:
        ApplicationRenderedEvent() = default;

      public:
        std::string ToString() const override;
        static EventType GetStaticType();
        virtual EventType GetEventType() const override;
        virtual const char* GetName() const override;
        virtual int GetCategoryFlags() const override;
    };
}
