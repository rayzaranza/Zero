#include "LayerStack.h"

namespace Zero
{
    LayerStack::LayerStack() : m_LayerInsert { m_Layers.begin() }
    {}

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_Layers)
        {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        LayerPointerArray::iterator layerIterator { std::find(m_Layers.begin(), m_Layers.end(), layer) };
        if (layerIterator != m_Layers.end())
        {
            m_Layers.erase(layerIterator);
            m_LayerInsert--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        LayerPointerArray::iterator layerIterator { std::find(m_Layers.begin(), m_Layers.end(), overlay) };
        if (layerIterator != m_Layers.end())
        {
            m_Layers.erase(layerIterator);
        }
    }

    LayerPointerArray::iterator LayerStack::begin()
    {
        return m_Layers.begin();
    }

    LayerPointerArray::iterator LayerStack::end()
    {
        return m_Layers.end();
    }
}
