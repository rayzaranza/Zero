#pragma once
#include "Zero/Layer/Layer.h"
#include "Zero/Core/Core.h"


namespace Zero {


class LayerStack
{
  public:
    LayerStack() = default;
    ~LayerStack();

  public:
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* layer);

  public:
    Array<Layer*>::iterator begin();
    Array<Layer*>::iterator end();
    Array<Layer*>::reverse_iterator rbegin();
    Array<Layer*>::reverse_iterator rend();

  private:
    Array<Layer*> m_Layers{};
    uint32_t m_LayerInsertIndex{ 0 };
};


}
