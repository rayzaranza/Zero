#pragma once

#include "Event.h"

namespace Zero
{
    // ················································································································
    //  Key Event
    // ················································································································
    class KeyEvent : public Event
    {
      public:
        int GetKeyCode() const;
        virtual int GetCategoryFlags() const override;

      protected:
        KeyEvent(int keyCode);

      protected:
        int m_KeyCode {};
    };

    // ················································································································
    //  Key Pressed Event
    // ················································································································
    class KeyPressedEvent : public KeyEvent
    {
      public:
        KeyPressedEvent(int keyCode, int repeatCount);

      public:
        int GetRepeatCount() const;
        std::string ToString() const override;
        static EventType GetStaticType();
        virtual EventType GetEventType() const override;
        virtual const char* GetName() const override;

      private:
        int m_RepeatCount {};
    };

    // ················································································································
    //  Key Released Event
    // ················································································································
    class KeyReleasedEvent : public KeyEvent
    {
      public:
        KeyReleasedEvent(int keyCode);

      public:
        std::string ToString() const override;
        static EventType GetStaticType();
        virtual EventType GetEventType() const override;
        virtual const char* GetName() const override;
    };

    // ················································································································
    //  Key Typed Event
    // ················································································································
    class KeyTypedEvent : public KeyEvent
    {
      public:
        KeyTypedEvent(int keyCode);

      public:
        std::string ToString() const override;
        static EventType GetStaticType();
        virtual EventType GetEventType() const override;
        virtual const char* GetName() const override;
    };
}
