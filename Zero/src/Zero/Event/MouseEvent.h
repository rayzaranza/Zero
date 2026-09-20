#pragma once
#include "Event.h"
#include "Zero/Core/Core.h"
#include "Zero/Input/MouseButton.h"

namespace Zero {
  class MouseMovedEvent : public Event {
  public:
    MouseMovedEvent(const glm::vec2& position);
    const glm::vec2& GetPosition() const;
    static EventType GetStaticType();
    virtual EventType GetEventType() const override;
    virtual const char* GetName() const override;
    virtual int32_t GetCategoryFlags() const override;
    virtual std::string ToString() const override;

  private:
    glm::vec2 m_Position;
  };

  class MouseScrolledEvent : public Event {
  public:
    MouseScrolledEvent(const glm::vec2& offset);
    const glm::vec2& GetOffset() const;
    static EventType GetStaticType();
    virtual EventType GetEventType() const override;
    virtual const char* GetName() const override;
    virtual int32_t GetCategoryFlags() const override;
    std::string ToString() const override;

  private:
    glm::vec2 m_Offset;
  };

  class MouseButtonEvent : public Event {
  public:
    MouseButton GetMouseButton() const;
    virtual int32_t GetCategoryFlags() const override;

  protected:
    MouseButtonEvent(const MouseButton button);
    MouseButton m_Button;
  };

  class MouseButtonPressedEvent : public MouseButtonEvent {
  public:
    MouseButtonPressedEvent(const MouseButton button);
    static EventType GetStaticType();
    virtual EventType GetEventType() const override;
    virtual const char* GetName() const override;
    virtual std::string ToString() const override;
  };

  class MouseButtonReleasedEvent : public MouseButtonEvent {
  public:
    MouseButtonReleasedEvent(const MouseButton button);
    static EventType GetStaticType();
    virtual EventType GetEventType() const override;
    virtual const char* GetName() const override;
    virtual std::string ToString() const override;
  };
}
