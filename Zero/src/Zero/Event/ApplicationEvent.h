#pragma once
#include "Zero/Event/Event.h"
#include "Zero/Core/Core.h"


namespace Zero {


class WindowResizedEvent : public Event
{
  public:
    WindowResizedEvent(const glm::ivec2& size);

  public:
    const glm::ivec2& GetSize() const;
    static EventType GetStaticType();
    virtual EventType GetEventType() const override;
    virtual const char* GetName() const override;
    virtual int32_t GetCategoryFlags() const override;
    virtual std::string ToString() const override;

  private:
    glm::ivec2 m_Size;
};


class WindowClosedEvent : public Event
{
  public:
    WindowClosedEvent() = default;

  public:
    static EventType GetStaticType();
    virtual EventType GetEventType() const override;
    virtual const char* GetName() const override;
    virtual int32_t GetCategoryFlags() const override;
    virtual std::string ToString() const override;
};


class ApplicationTickedEvent : public Event
{
  public:
    ApplicationTickedEvent() = default;

  public:
    static EventType GetStaticType();
    virtual EventType GetEventType() const override;
    virtual const char* GetName() const override;
    virtual int32_t GetCategoryFlags() const override;
    virtual std::string ToString() const override;
};


class ApplicationUpdatedEvent : public Event
{
  public:
    ApplicationUpdatedEvent() = default;

  public:
    static EventType GetStaticType();
    virtual EventType GetEventType() const override;
    virtual const char* GetName() const override;
    virtual int32_t GetCategoryFlags() const override;
    virtual std::string ToString() const override;
};


class ApplicationRenderedEvent : public Event
{
  public:
    ApplicationRenderedEvent() = default;

  public:
    static EventType GetStaticType();
    virtual EventType GetEventType() const override;
    virtual const char* GetName() const override;
    virtual int32_t GetCategoryFlags() const override;
    virtual std::string ToString() const override;
};


}
