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
        KeyTyped,
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
        EventCategoryApplication = ZERO_BIT_SHIFT(0),
        EventCategoryInput = ZERO_BIT_SHIFT(1),
        EventCategoryKeyboard = ZERO_BIT_SHIFT(2),
        EventCategoryMouse = ZERO_BIT_SHIFT(3),
        EventCategoryMouseButton = ZERO_BIT_SHIFT(4)
    };

    // ················································································································
    //  Event
    // ················································································································
    class Event
    {
      public:
        virtual ~Event() = default;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;

      public:
        inline virtual std::string ToString() const { return GetName(); }
        inline bool IsHandled() const { return m_IsHandled; }
        inline bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; };

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
        EventDispatcher(Event& event) : m_Event { event } {}

      protected:
        template <typename T>
        using EventCallback = std::function<bool(T&)>;

      public:
        template <typename T>
        bool Dispatch(EventCallback<T> function)
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

template <>
struct fmt::formatter<Zero::Event> : fmt::ostream_formatter
{};
