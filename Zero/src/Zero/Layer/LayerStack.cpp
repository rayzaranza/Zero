#include "Zero/Layer/LayerStack.h"

namespace Zero
{
    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_Layers)
        {
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        Array<Layer*>::iterator layerIterator{ std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer) };
        if (layerIterator != m_Layers.end() + m_LayerInsertIndex)
        {
            layer->OnDetach();
            m_Layers.erase(layerIterator);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        Array<Layer*>::iterator layerIterator{ std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay) };
        if (layerIterator != m_Layers.end())
        {
            overlay->OnDetach();
            m_Layers.erase(layerIterator);
        }
    }
}
