#pragma once

#include "Event.h"

namespace Zero
{
    //=====================================================================================================================================
    //  Key Event
    //=====================================================================================================================================

    class KeyEvent : public Event
    {
      public:
        inline int GetKeyCode() const { return m_KeyCode; }
        inline virtual int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

      protected:
        KeyEvent(int keyCode) : m_KeyCode { keyCode } {}

      protected:
        int m_KeyCode {};
    };

    //=====================================================================================================================================
    //  Key Pressed Event
    //=====================================================================================================================================

    class KeyPressedEvent : public KeyEvent
    {
      public:
        KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent { keyCode }, m_RepeatCount { repeatCount } {}

      public:
        inline int GetRepeatCount() const { return m_RepeatCount; }
        inline static EventType GetStaticType() { return EventType::KeyPressed; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "KeyPressed"; }
        inline virtual std::string ToString() const override
        {
            std::stringstream stream {};
            stream << "KeyPressedEvent: " << m_KeyCode << " (repeats: " << m_RepeatCount << ")";
            return stream.str();
        }

      private:
        int m_RepeatCount {};
    };

    //=====================================================================================================================================
    //  Key Released Event
    //=====================================================================================================================================

    class KeyReleasedEvent : public KeyEvent
    {
      public:
        KeyReleasedEvent(int keyCode) : KeyEvent { keyCode } {}

      public:
        inline static EventType GetStaticType() { return EventType::KeyReleased; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "KeyReleased"; }
        inline virtual std::string ToString() const override
        {
            std::stringstream stream {};
            stream << "KeyReleasedEvent: " << m_KeyCode;
            return stream.str();
        }
    };

    //=====================================================================================================================================
    //  Key Typed Event
    //=====================================================================================================================================

    class KeyTypedEvent : public KeyEvent
    {
      public:
        KeyTypedEvent(int keyCode) : KeyEvent { keyCode } {}

      public:
        inline static EventType GetStaticType() { return EventType::KeyTyped; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); };
        inline virtual const char* GetName() const override { return "KeyTyped"; };
        inline virtual std::string ToString() const override
        {
            std::stringstream stream {};
            stream << "KeyTypedEvent: " << m_KeyCode;
            return stream.str();
        }
    };
}
