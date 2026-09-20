#include "ApplicationEvent.h"

//======================================================================================================
//  Window Resized
//======================================================================================================
Zero::WindowResizedEvent::WindowResizedEvent(const glm::ivec2& size) : m_Size{ size } {
}

const glm::ivec2& Zero::WindowResizedEvent::GetSize() const {
  return m_Size;
}

Zero::EventType Zero::WindowResizedEvent::GetStaticType() {
  return EventType::WindowResized;
}

Zero::EventType Zero::WindowResizedEvent::GetEventType() const {
  return GetStaticType();
}

const char* Zero::WindowResizedEvent::GetName() const {
  return "WindowResized";
}

int32_t Zero::WindowResizedEvent::GetCategoryFlags() const {
  return EventCategory::EventCategoryApplication;
}

std::string Zero::WindowResizedEvent::ToString() const {
  std::stringstream stream{};
  stream << GetName() << ": " << m_Size.x << ", " << m_Size.y;
  return stream.str();
}

//======================================================================================================
//  Window Closed
//======================================================================================================
Zero::EventType Zero::WindowClosedEvent::GetStaticType() {
  return EventType::WindowClosed;
}

Zero::EventType Zero::WindowClosedEvent::GetEventType() const {
  return GetStaticType();
}

const char* Zero::WindowClosedEvent::GetName() const {
  return "WindowClosed";
}

int32_t Zero::WindowClosedEvent::GetCategoryFlags() const {
  return EventCategoryApplication;
}

std::string Zero::WindowClosedEvent::ToString() const {
  return GetName();
}

//======================================================================================================
//  Application Ticked
//======================================================================================================
Zero::EventType Zero::ApplicationTickedEvent::GetStaticType() {
  return EventType::ApplicationTicked;
}

Zero::EventType Zero::ApplicationTickedEvent::GetEventType() const {
  return GetStaticType();
}

const char* Zero::ApplicationTickedEvent::GetName() const {
  return "ApplicationTicked";
}

int32_t Zero::ApplicationTickedEvent::GetCategoryFlags() const {
  return EventCategoryApplication;
}

std::string Zero::ApplicationTickedEvent::ToString() const {
  return GetName();
}

//======================================================================================================
//  Application Updated
//======================================================================================================
Zero::EventType Zero::ApplicationUpdatedEvent::GetStaticType() {
  return EventType::ApplicationUpdated;
}

Zero::EventType Zero::ApplicationUpdatedEvent::GetEventType() const {
  return GetStaticType();
}

const char* Zero::ApplicationUpdatedEvent::GetName() const {
  return "ApplicationUpdated";
}

int32_t Zero::ApplicationUpdatedEvent::GetCategoryFlags() const {
  return EventCategoryApplication;
}

std::string Zero::ApplicationUpdatedEvent::ToString() const {
  return GetName();
}

//======================================================================================================
//  Application Rendered
//======================================================================================================
Zero::EventType Zero::ApplicationRenderedEvent::GetStaticType() {
  return EventType::ApplicationRendered;
}

Zero::EventType Zero::ApplicationRenderedEvent::GetEventType() const {
  return GetStaticType();
}

const char* Zero::ApplicationRenderedEvent::GetName() const {
  return "ApplicationRendered";
}

int32_t Zero::ApplicationRenderedEvent::GetCategoryFlags() const {
  return EventCategoryApplication;
}

std::string Zero::ApplicationRenderedEvent::ToString() const {
  return GetName();
}
