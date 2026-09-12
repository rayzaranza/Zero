#pragma once

#include "Zero/Core/Core.h"
#include "Zero/Event/Event.h"

namespace Zero
{
    //=====================================================================================================================================
    //  Mouse Moved Event
    //=====================================================================================================================================
    class MouseMovedEvent : public Event
    {
      public:
        MouseMovedEvent(const Vector2& position) : m_Position{ position } {}

      public:
        inline const Vector2& GetPosition() const { return m_Position; }
        inline static EventType GetStaticType() { return EventType::MouseMoved; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "MouseMoved"; }
        inline virtual I32 GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        inline virtual String ToString() const override
        {
            std::stringstream stream{};
            stream << "MouseMovedEvent: " << m_Position.x << ", " << m_Position.y;
            return stream.str();
        }

      private:
        Vector2 m_Position;
    };

    //=====================================================================================================================================
    //  Mouse Scrolled Event
    //=====================================================================================================================================
    class MouseScrolledEvent : public Event
    {
      public:
        MouseScrolledEvent(const Vector2& offset) : m_Offset{ offset } {}

      public:
        inline const Vector2& GetOffset() const { return m_Offset; }
        inline static EventType GetStaticType() { return EventType::MouseScrolled; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "MouseScrolled"; }
        inline virtual I32 GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        inline String ToString() const override
        {
            std::stringstream stream{};
            stream << "MouseScrolledEvent: " << m_Offset.x << ", " << m_Offset.y;
            return stream.str();
        }

      private:
        Vector2 m_Offset;
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
        MouseButtonEvent(const I32 button) : m_Button{ button } {}

      protected:
        I32 m_Button;
    };

    //=====================================================================================================================================
    //  Mouse Button Pressed Event
    //=====================================================================================================================================
    class MouseButtonPressedEvent : public MouseButtonEvent
    {
      public:
        MouseButtonPressedEvent(const I32 button) : MouseButtonEvent{ button } {}

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
        MouseButtonReleasedEvent(const I32 button) : MouseButtonEvent{ button } {}

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
