#pragma once

#include "Zero/Core.h"

namespace Zero
{
    // ················································································································
    //  Event Type
    // ················································································································
    enum class EventType
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
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    // ················································································································
    //  Event Category
    // ················································································································
    enum EventCategory
    {
        None,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

    // ················································································································
    //  Event
    // ················································································································
    class ZERO_API Event
    {
      public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const;

      public:
        bool IsInCategory(EventCategory category) const;
        bool IsHandled() const;

      protected:
        bool m_IsHandled { false };
        friend class EventDispatcher;
    };

    inline std::ostream& operator<<(std::ostream& stream, const Event& event)
    {
        return stream << event.ToString();
    }

    // ················································································································
    //  Event Dispatcher
    // ················································································································
    class EventDispatcher
    {
      public:
        EventDispatcher(Event& event);

      protected:
        template <typename T> using EventCallback = std::function<bool(T&)>;

      public:
        template <typename T> bool Dispatch(EventCallback<T> function);

      private:
        Event& m_Event;
    };

    template <typename T> inline bool EventDispatcher::Dispatch(EventCallback<T> callback)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.m_IsHandled = callback(*(T*)&m_Event);
            return true;
        }

        return false;
    }

}

template <> struct fmt::formatter<Zero::Event> : fmt::ostream_formatter
{};
