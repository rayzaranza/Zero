#include "Event.h"

namespace Zero
{
    EventDispatcher::EventDispatcher(Event& event) : m_Event { event }
    {}

    bool Event::IsInCategory(EventCategory category) const
    {
        return GetCategoryFlags() & category;
    }

    bool Event::IsHandled() const
    {
        return m_IsHandled;
    }

    std::string Event::ToString() const
    {
        return GetName();
    }
}
