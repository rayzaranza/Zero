#include "MouseEvent.h"

//=====================================================================================================================================
//  Mouse Moved Event
//=====================================================================================================================================
Zero::MouseMovedEvent::MouseMovedEvent(const glm::vec2& position) : m_Position{ position } {
}

const glm::vec2& Zero::MouseMovedEvent::GetPosition() const {
  return m_Position;
}

Zero::EventType Zero::MouseMovedEvent::GetStaticType() {
  return EventType::MouseMoved;
}

Zero::EventType Zero::MouseMovedEvent::GetEventType() const {
  return GetStaticType();
}

const char* Zero::MouseMovedEvent::GetName() const {
  return "MouseMoved";
}

int32_t Zero::MouseMovedEvent::GetCategoryFlags() const {
  return EventCategoryMouse | EventCategoryInput;
}

std::string Zero::MouseMovedEvent::ToString() const {
  std::stringstream stream{};
  stream << "MouseMovedEvent: " << m_Position.x << ", " << m_Position.y;
  return stream.str();
}

//=====================================================================================================================================
//  Mouse Scrolled Event
//=====================================================================================================================================
Zero::MouseScrolledEvent::MouseScrolledEvent(const glm::vec2& offset) : m_Offset{ offset } {
}

const glm::vec2& Zero::MouseScrolledEvent::GetOffset() const {
  return m_Offset;
}

Zero::EventType Zero::MouseScrolledEvent::GetStaticType() {
  return EventType::MouseScrolled;
}

Zero::EventType Zero::MouseScrolledEvent::GetEventType() const {
  return GetStaticType();
}

const char* Zero::MouseScrolledEvent::GetName() const {
  return "MouseScrolled";
}

int32_t Zero::MouseScrolledEvent::GetCategoryFlags() const {
  return EventCategoryMouse | EventCategoryInput;
}

std::string Zero::MouseScrolledEvent::ToString() const {
  return GetName();
}

//=====================================================================================================================================
//  Mouse Button Event
//=====================================================================================================================================
Zero::MouseButtonEvent::MouseButtonEvent(const MouseButton button) : m_Button{ button } {
}

Zero::MouseButton Zero::MouseButtonEvent::GetMouseButton() const {
  return m_Button;
}

int32_t Zero::MouseButtonEvent::GetCategoryFlags() const {
  return EventCategoryMouseButton | EventCategoryInput;
}

//=====================================================================================================================================
//  Mouse Button Pressed Event
//=====================================================================================================================================
Zero::MouseButtonPressedEvent::MouseButtonPressedEvent(const MouseButton button) : MouseButtonEvent{ button } {
}

Zero::EventType Zero::MouseButtonPressedEvent::GetStaticType() {
  return EventType::MouseButtonPressed;
}

Zero::EventType Zero::MouseButtonPressedEvent::GetEventType() const {
  return GetStaticType();
}

const char* Zero::MouseButtonPressedEvent::GetName() const {
  return "MouseButtonPressed";
}

std::string Zero::MouseButtonPressedEvent::ToString() const {
  std::stringstream stream{};
  stream << "MouseButtonPressedEvent: " << static_cast<uint32_t>(m_Button);
  return stream.str();
}

//=====================================================================================================================================
//  Mouse Button Released Event
//=====================================================================================================================================
Zero::MouseButtonReleasedEvent::MouseButtonReleasedEvent(const MouseButton button) : MouseButtonEvent{ button } {
}

Zero::EventType Zero::MouseButtonReleasedEvent::GetStaticType() {
  return EventType::MouseButtonReleased;
}

Zero::EventType Zero::MouseButtonReleasedEvent::GetEventType() const {
  return GetStaticType();
}

const char* Zero::MouseButtonReleasedEvent::GetName() const {
  return "MouseButtonReleased";
}

std::string Zero::MouseButtonReleasedEvent::ToString() const {
  std::stringstream stream{};
  stream << "MouseButtonReleasedEvent: " << static_cast<uint32_t>(m_Button);
  return stream.str();
}
