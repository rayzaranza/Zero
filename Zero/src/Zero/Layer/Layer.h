#pragma once
#include "Zero/Core/Core.h"
#include "Zero/Event/Event.h"
#include "Zero/Time/DeltaTime.h"


namespace Zero {


class Layer
{
  public:
    Layer(const std::string& name = "Layer");

  public:
    const std::string& GetName() const;

  public:
    virtual void OnAttach();
    virtual void OnDetach();
    virtual void OnUpdate(const DeltaTime deltaTime);
    virtual void OnRender();
    virtual void OnUIRender();
    virtual void OnEvent(Event& event);

  private:
    std::string m_Name;
};


}
