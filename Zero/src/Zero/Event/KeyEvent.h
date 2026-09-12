#pragma once

#include "Zero/Event/Event.h"
#include "Zero/Input/KeyCode.h"

namespace Zero
{
    //=====================================================================================================================================
    //  Key Event
    //=====================================================================================================================================
    class KeyEvent : public Event
    {
      public:
        inline KeyCode GetKeyCode() const { return m_KeyCode; }
        inline virtual I32 GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

      protected:
        KeyEvent(const KeyCode keyCode) : m_KeyCode{ keyCode } {}

      protected:
        KeyCode m_KeyCode{};
    };

    //=====================================================================================================================================
    //  Key Pressed Event
    //=====================================================================================================================================
    class KeyPressedEvent : public KeyEvent
    {
      public:
        KeyPressedEvent(const KeyCode keyCode, const I32 repeatCount) : KeyEvent{ keyCode }, m_RepeatCount{ repeatCount } {}

      public:
        inline I32 GetRepeatCount() const { return m_RepeatCount; }
        inline static EventType GetStaticType() { return EventType::KeyPressed; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "KeyPressed"; }
        inline virtual String ToString() const override
        {
            std::stringstream stream{};
            stream << "KeyPressedEvent: " << static_cast<char>(m_KeyCode) << " (repeats: " << m_RepeatCount << ")";
            return stream.str();
        }

      private:
        I32 m_RepeatCount;
    };

    //=====================================================================================================================================
    //  Key Released Event
    //=====================================================================================================================================
    class KeyReleasedEvent : public KeyEvent
    {
      public:
        KeyReleasedEvent(const KeyCode keyCode) : KeyEvent{ keyCode } {}

      public:
        inline static EventType GetStaticType() { return EventType::KeyReleased; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); }
        inline virtual const char* GetName() const override { return "KeyReleased"; }
        inline virtual String ToString() const override
        {
            std::stringstream stream{};
            stream << "KeyReleasedEvent: " << static_cast<char>(m_KeyCode);
            return stream.str();
        }
    };

    //=====================================================================================================================================
    //  Key Typed Event
    //=====================================================================================================================================
    class KeyTypedEvent : public KeyEvent
    {
      public:
        KeyTypedEvent(const KeyCode keyCode) : KeyEvent{ keyCode } {}

      public:
        inline static EventType GetStaticType() { return EventType::KeyTyped; }
        inline virtual EventType GetEventType() const override { return GetStaticType(); };
        inline virtual const char* GetName() const override { return "KeyTyped"; };
        inline virtual String ToString() const override
        {
            std::stringstream stream{};
            stream << "KeyTypedEvent: " << static_cast<char>(m_KeyCode);
            return stream.str();
        }
    };
}
