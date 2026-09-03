#pragma once

#include "Event.h"

namespace Zero
{
    // ················································································································
    //  Key Event
    // ················································································································
    class ZERO_API KeyEvent : public Event
    {
      public:
        inline int GetKeyCode() const;
        virtual int GetCategoryFlags() const override;

      protected:
        KeyEvent(int keyCode);

      protected:
        int m_KeyCode {};
    };

    // ················································································································
    //  Key Pressed Event
    // ················································································································
    class ZERO_API KeyPressedEvent : public KeyEvent
    {
      public:
        KeyPressedEvent(int keyCode, int repeatCount);

      public:
        inline int GetRepeatCount() const;
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
    class ZERO_API KeyReleasedEvent : public KeyEvent
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
    class ZERO_API KeyTypedEvent : public KeyEvent
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
