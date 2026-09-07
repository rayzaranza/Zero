#pragma once

#include "Layer.h"
#include "Zero/Core.h"

namespace Zero
{
    class LayerStack
    {
      public:
        LayerStack();
        ~LayerStack();

      public:
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* layer);

        std::vector<Layer*>::iterator begin();
        std::vector<Layer*>::iterator end();

      private:
        std::vector<Layer*> m_Layers {};
        unsigned int m_LayerInsertIndex { 0 };
    };
}
