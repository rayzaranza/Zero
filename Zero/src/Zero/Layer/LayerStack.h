#pragma once

#include "Zero/Core/Core.h"
#include "Zero/Layer/Layer.h"

namespace Zero
{
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
        inline Array<Layer*>::iterator begin() { return m_Layers.begin(); }
        inline Array<Layer*>::iterator end() { return m_Layers.end(); }

      private:
        Array<Layer*> m_Layers{};
        U32 m_LayerInsertIndex{ 0 };
    };
}
