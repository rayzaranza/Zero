#include "Event.h"

std::string Zero::Event::ToString() const {
  return GetName();
}

bool Zero::Event::IsHandled() const {
  return m_IsHandled;
}

bool Zero::Event::IsInCategory(EventCategory category) const {
  return GetCategoryFlags() & category;
}

Zero::EventDispatcher::EventDispatcher(Event& event) : m_Event{ event } {
}

std::ostream& operator<<(std::ostream& stream, const Zero::Event& event) {
  return stream << event.ToString();
}
