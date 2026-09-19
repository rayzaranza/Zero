#pragma once
#include "Zero/Layer/Layer.h"

namespace Zero {
  class UILayer : public Layer {
  public:
    UILayer();
    ~UILayer() = default;
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUIRender() override;
    void Begin();
    void End();

  private:
    float m_Time;
  };
}
