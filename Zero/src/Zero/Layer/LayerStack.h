#pragma once

#include "Layer.h"
#include "Zero/Core.h"

namespace Zero
{
    using LayerPointerArray = std::vector<Layer*>;

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

        LayerPointerArray::iterator begin();
        LayerPointerArray::iterator end();

      private:
        LayerPointerArray m_Layers {};
        unsigned int m_LayerInsertIndex { 0 };
    };
}
