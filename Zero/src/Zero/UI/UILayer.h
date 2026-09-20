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
  virtual void OnEvent(Event& event) override;
  void Begin();
  void End();
  void SetIsBlockingEvents(const bool isBlocking);
private:
  float m_Time;
  bool m_IsBlockingEvents{ true };
};

}
