#include "Event.h"

std::string Zero::Event::ToString() const {
  return GetName();
}

bool Zero::Event::IsInCategory(EventCategory category) const {
  return GetCategoryFlags() & category;
}

Zero::EventDispatcher::EventDispatcher(Event& event) : m_Event{ event } {
}

std::ostream& Zero::operator<<(std::ostream& stream, const Event& event) {
  return stream << event.ToString();
}
