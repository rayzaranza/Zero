#pragma once
#include "Zero/Core.h"
#include <fmt/format.h>
#include <functional>
#include <ostream>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>
#include <string>

namespace Zero
{
    //················································································································
    // Event Type
    //················································································································
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

    //················································································································
    // Event Category
    //················································································································
    enum EventCategory
    {
        None,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

    //················································································································
    // Event 
    //················································································································
    class ZERO_API Event
    {
    protected:
        bool m_IsHandled { false };
        friend class EventDispatcher;

    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;

    public:
        virtual std::string ToString() const;
        bool IsInCategory(EventCategory category) const;
    };

    inline std::string format_as(const Event& event)
    {
        return event.ToString();
    }


    //················································································································
    // Event Dispatcher
    //················································································································
    class EventDispatcher
    {
    private:
        Event& m_Event;

    protected:
        template <typename T>
        using EventCallback = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& event);

    public:
        template <typename T>
        bool Dispatch(EventCallback<T> function);
    };

    template <typename T>
    inline bool EventDispatcher::Dispatch(EventCallback<T> function)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.m_IsHandled = function(*(T*)&m_Event);
            return true;
        }

        return false;
    }
}


