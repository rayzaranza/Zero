#pragma once

#include "Zero/Core/Core.h"

namespace Zero
{
    //======================================================================================
    //  Event Type
    //======================================================================================
    enum class EventType : U8
    {
        None,
        WindowClosed,
        WindowResized,
        WindowFocused,
        WindowLostFocus,
        WindowMoved,
        ApplicationTicked,
        ApplicationUpdated,
        ApplicationRendered,
        KeyPressed,
        KeyReleased,
        KeyTyped,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled,
    };

    //======================================================================================
    //  Event Category
    //======================================================================================
    enum EventCategory : U8
    {
        None,
        EventCategoryApplication = 1 << 0,
        EventCategoryInput = 1 << 1,
        EventCategoryKeyboard = 1 << 2,
        EventCategoryMouse = 1 << 3,
        EventCategoryMouseButton = 1 << 4,
    };

    //======================================================================================
    //  Event
    //======================================================================================
    class Event
    {
      public:
        virtual ~Event() = default;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual I32 GetCategoryFlags() const = 0;

      public:
        inline virtual String ToString() const { return GetName(); }
        inline Boolean IsHandled() const { return m_IsHandled; }
        inline Boolean IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; };

      protected:
        Boolean m_IsHandled{ false };
        friend class EventDispatcher;
    };

    inline std::ostream& operator<<(std::ostream& stream, const Event& event)
    {
        return stream << event.ToString();
    }

    //======================================================================================
    //  Event Dispatcher
    //======================================================================================
    class EventDispatcher
    {
      public:
        EventDispatcher(Event& event) : m_Event{ event } {}

      public:
        template <typename T> Boolean Dispatch(Function<Boolean(T&)> function)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.m_IsHandled = function(*(T*)&m_Event);
                return true;
            }
            return false;
        }

      private:
        Event& m_Event;
    };

}

template <> struct fmt::formatter<Zero::Event> : fmt::ostream_formatter
{};
