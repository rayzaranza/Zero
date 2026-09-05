#pragma once

#include "Event.h"
#include "Zero/Core.h"

namespace Zero
{
    // ················································································································
    //  Mouse Moved Event
    // ················································································································
    class MouseMovedEvent : public Event
    {
      public:
        MouseMovedEvent(float x, float y);

      public:
        inline float GetX() const;
        inline float GetY() const;
        std::string ToString() const override;
        static EventType GetStaticType();
        virtual EventType GetEventType() const override;
        virtual const char* GetName() const override;
        virtual int GetCategoryFlags() const override;

      private:
        float m_MouseX {};
        float m_MouseY {};
    };

    // ················································································································
    //  Mouse Scrolled Event
    // ················································································································
    class MouseScrolledEvent : public Event
    {
      public:
        MouseScrolledEvent(float xOffset, float yOffset);

      public:
        inline float GetXOffset() const;
        inline float GetYOffset() const;
        std::string ToString() const override;
        static EventType GetStaticType();
        virtual EventType GetEventType() const override;
        virtual const char* GetName() const override;
        virtual int GetCategoryFlags() const override;

      private:
        float m_XOffset {};
        float m_YOffset {};
    };

    // ················································································································
    //  Mouse Button Event
    // ················································································································
    class MouseButtonEvent : public Event
    {
      public:
        inline int GetMouseButton() const;
        virtual int GetCategoryFlags() const override;

      protected:
        MouseButtonEvent(int button);

      protected:
        int m_Button {};
    };

    // ················································································································
    //  Mouse Button Pressed Event
    // ················································································································
    class MouseButtonPressedEvent : public MouseButtonEvent
    {
      public:
        MouseButtonPressedEvent(int button);

      public:
        std::string ToString() const override;
        static EventType GetStaticType();
        virtual EventType GetEventType() const override;
        virtual const char* GetName() const override;
    };

    // ················································································································
    //  Mouse Button Released Event
    // ················································································································
    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
      public:
        MouseButtonReleasedEvent(int button);

      public:
        std::string ToString() const override;
        static EventType GetStaticType();
        virtual EventType GetEventType() const override;
        virtual const char* GetName() const override;
    };
}
