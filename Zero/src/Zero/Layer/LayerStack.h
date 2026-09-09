#pragma once

#include "Zero/Core.h"
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
        inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }

      private:
        std::vector<Layer*> m_Layers{};
        unsigned int m_LayerInsertIndex{0};
    };
}
