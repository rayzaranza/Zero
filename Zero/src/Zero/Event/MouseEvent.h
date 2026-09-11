#pragma once

#include "Zero/Core.h"

#include "Event.h"

namespace Zero
{
    //=====================================================================================================================================
    //  Mouse Moved Event
    //=====================================================================================================================================
    class MouseMovedEvent : public Event
    {
      public:
        MouseMovedEvent(F32 x, F32 y) : m_MouseX{ x }, m_MouseY{ y } {}

      public:
        inline F32 GetX() const { return m_MouseX; }
        inline F32 GetY() const { return m_MouseY; }
        inline static EventType GetStaticType() { return EventType::MouseMoved; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "MouseMoved"; }
        inline virtual I32 GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        inline virtual String ToString() const override
        {
            std::stringstream stream{};
            stream << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return stream.str();
        }

      private:
        F32 m_MouseX;
        F32 m_MouseY;
    };

    //=====================================================================================================================================
    //  Mouse Scrolled Event
    //=====================================================================================================================================
    class MouseScrolledEvent : public Event
    {
      public:
        MouseScrolledEvent(F32 xOffset, F32 yOffset) : m_XOffset{ xOffset }, m_YOffset{ yOffset } {}

      public:
        inline F32 GetXOffset() const { return m_XOffset; }
        inline F32 GetYOffset() const { return m_YOffset; }
        inline static EventType GetStaticType() { return EventType::MouseScrolled; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "MouseScrolled"; }
        inline virtual I32 GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        inline String ToString() const override
        {
            std::stringstream stream{};
            stream << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
            return stream.str();
        }

      private:
        F32 m_XOffset;
        F32 m_YOffset;
    };

    //=====================================================================================================================================
    //  Mouse Button Event
    //=====================================================================================================================================
    class MouseButtonEvent : public Event
    {
      public:
        inline I32 GetMouseButton() const { return m_Button; }
        inline virtual I32 GetCategoryFlags() const override { return EventCategoryMouseButton | EventCategoryInput; };

      protected:
        MouseButtonEvent(I32 button) : m_Button{ button } {}

      protected:
        I32 m_Button;
    };

    //=====================================================================================================================================
    //  Mouse Button Pressed Event
    //=====================================================================================================================================
    class MouseButtonPressedEvent : public MouseButtonEvent
    {
      public:
        MouseButtonPressedEvent(I32 button) : MouseButtonEvent{ button } {}

      public:
        inline static EventType GetStaticType() { return EventType::MouseButtonPressed; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "MouseButtonPressed"; }
        inline virtual String ToString() const override
        {
            std::stringstream stream{};
            stream << "MouseButtonPressedEvent: " << m_Button;
            return stream.str();
        }
    };

    //=====================================================================================================================================
    //  Mouse Button Released Event
    //=====================================================================================================================================
    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
      public:
        MouseButtonReleasedEvent(I32 button) : MouseButtonEvent{ button } {}

      public:
        inline static EventType GetStaticType() { return EventType::MouseButtonReleased; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "MouseButtonReleased"; }
        inline virtual String ToString() const override
        {
            std::stringstream stream{};
            stream << "MouseButtonReleasedEvent: " << m_Button;
            return stream.str();
        }
    };
}
