#include "Event.h"

namespace Zero
{
    EventDispatcher::EventDispatcher(Event& event)
        : m_Event { event }
    {}

    bool Event::IsInCategory(EventCategory category) const
    {
        return GetCategoryFlags() & category;
    }

    std::string Event::ToString() const
    {
        return GetName();
    }

    std::ostream& operator << (std::ostream& stream, Event& event)
    {
        return stream << event.ToString();
    }
}
