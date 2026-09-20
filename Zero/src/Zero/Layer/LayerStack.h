#pragma once
#include "Layer.h"
#include "Zero/Core/Core.h"

namespace Zero {

class LayerStack {
public:
  LayerStack() = default;
  ~LayerStack();
  void PushLayer(Layer* layer);
  void PushOverlay(Layer* overlay);
  void PopLayer(Layer* layer);
  void PopOverlay(Layer* layer);
  Array<Layer*>::iterator begin();
  Array<Layer*>::iterator end();
  Array<Layer*>::reverse_iterator rbegin();
  Array<Layer*>::reverse_iterator rend();

private:
  Array<Layer*> m_Layers{};
  uint32_t m_LayerInsertIndex{ 0 };
};

}
