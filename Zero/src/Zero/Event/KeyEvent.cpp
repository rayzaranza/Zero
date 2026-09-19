#include "KeyEvent.h"

//=====================================================================================================================================
//  Key Event
//=====================================================================================================================================
Zero::KeyEvent::KeyEvent(const KeyCode keyCode) : m_KeyCode{ keyCode } {
}

Zero::KeyCode Zero::KeyEvent::GetKeyCode() const {
  return m_KeyCode;
}

int32_t Zero::KeyEvent::GetCategoryFlags() const {
  return EventCategoryKeyboard | EventCategoryInput;
}

//=====================================================================================================================================
//  Key Pressed Event
//=====================================================================================================================================
Zero::KeyPressedEvent::KeyPressedEvent(const KeyCode keyCode, const int32_t repeatCount) : KeyEvent{ keyCode }, m_RepeatCount{ repeatCount } {
}

inline int32_t Zero::KeyPressedEvent::GetRepeatCount() const {
  return m_RepeatCount;
}

inline Zero::EventType Zero::KeyPressedEvent::GetStaticType() {
  return EventType::KeyPressed;
}

inline Zero::EventType Zero::KeyPressedEvent::GetEventType() const {
  return GetStaticType();
}

inline const char* Zero::KeyPressedEvent::GetName() const {
  return "KeyPressed";
}

inline std::string Zero::KeyPressedEvent::ToString() const {
  std::stringstream stream{};
  stream << "KeyPressedEvent: " << static_cast<char>(m_KeyCode) << " (repeats: " << m_RepeatCount << ")";
  return stream.str();
}

//=====================================================================================================================================
//  Key Released Event
//=====================================================================================================================================
Zero::KeyReleasedEvent::KeyReleasedEvent(const KeyCode keyCode) : KeyEvent{ keyCode } {
}

Zero::EventType Zero::KeyReleasedEvent::GetStaticType() {
  return EventType::KeyReleased;
}

Zero::EventType Zero::KeyReleasedEvent::GetEventType() const {
  return GetStaticType();
}

const char* Zero::KeyReleasedEvent::GetName() const {
  return "KeyReleased";
}

std::string Zero::KeyReleasedEvent::ToString() const {
  std::stringstream stream{};
  stream << "KeyReleasedEvent: " << static_cast<char>(m_KeyCode);
  return stream.str();
}

//=====================================================================================================================================
//  Key Typed Event
//=====================================================================================================================================
Zero::KeyTypedEvent::KeyTypedEvent(const KeyCode keyCode) : KeyEvent{ keyCode } {
}

Zero::EventType Zero::KeyTypedEvent::GetStaticType() {
  return EventType::KeyTyped;
}

Zero::EventType Zero::KeyTypedEvent::GetEventType() const {
  return GetStaticType();
}

const char* Zero::KeyTypedEvent::GetName() const {
  return "KeyTyped";
}

std::string Zero::KeyTypedEvent::ToString() const {
  std::stringstream stream{};
  stream << "KeyTypedEvent: " << static_cast<char>(m_KeyCode);
  return stream.str();
}
