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
        MouseMovedEvent(float x, float y) : m_MouseX { x }, m_MouseY { y } {}

      public:
        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }
        inline static EventType GetStaticType() { return EventType::MouseMoved; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "MouseMoved"; }
        inline virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        inline virtual std::string ToString() const override
        {
            std::stringstream stream {};
            stream << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return stream.str();
        }

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
        MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset { xOffset }, m_YOffset { yOffset } {}

      public:
        inline float GetXOffset() const { return m_XOffset; }
        inline float GetYOffset() const { return m_YOffset; }
        inline static EventType GetStaticType() { return EventType::MouseScrolled; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "MouseScrolled"; }
        inline virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        inline std::string ToString() const override
        {
            std::stringstream stream {};
            stream << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
            return stream.str();
        }

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
        inline int GetMouseButton() const { return m_Button; }
        inline virtual int GetCategoryFlags() const override { return EventCategoryMouseButton | EventCategoryInput; };

      protected:
        MouseButtonEvent(int button) : m_Button { button } {}

      protected:
        int m_Button {};
    };

    // ················································································································
    //  Mouse Button Pressed Event
    // ················································································································
    class MouseButtonPressedEvent : public MouseButtonEvent
    {
      public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent { button } {}

      public:
        inline static EventType GetStaticType() { return EventType::MouseButtonPressed; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "MouseButtonPressed"; }
        inline virtual std::string ToString() const override
        {
            std::stringstream stream {};
            stream << "MouseButtonPressedEvent: " << m_Button;
            return stream.str();
        }
    };

    // ················································································································
    //  Mouse Button Released Event
    // ················································································································
    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
      public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent { button } {}

      public:
        inline static EventType GetStaticType() { return EventType::MouseButtonReleased; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "MouseButtonReleased"; }
        inline virtual std::string ToString() const override
        {
            std::stringstream stream {};
            stream << "MouseButtonReleasedEvent: " << m_Button;
            return stream.str();
        }
    };
}
