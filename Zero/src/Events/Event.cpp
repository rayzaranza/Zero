#include "Event.h"

namespace Zero
{
    EventDispatcher::EventDispatcher(Event& event) : m_Event { event }
    {}

    bool Event::IsInCategory(EventCategory category) const
    {
        return GetCategoryFlags() & category;
    }

    std::string Event::ToString() const
    {
        return GetName();
    }

    std::string format_as(const Event& event)
    {
        return event.ToString();
    }
}
